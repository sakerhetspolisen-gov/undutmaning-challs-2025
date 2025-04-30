#!/usr/bin/env -S python3

import sys
import time
import socket

from pyrenode3.wrappers import Analyzer, Emulation, Monitor

import System

from Antmicro.Renode.Core import EmulationManager
from Antmicro.Renode.Peripherals.UART import IUART
from Antmicro.Renode.Peripherals.CPU import ICpuSupportingGdb, RegisterValue, ExecutionMode
from Antmicro.Renode.Utilities import ReadFilePath

HOST = "127.0.0.1"
PORT = 4000 + int(sys.argv[1])

print(f"Running glitch-emulator service on port {PORT}")

# Print to the connected socket
current_conn = None
def out(text="", end="\n"):
    if current_conn:
        try:
            current_conn.sendall((text + end).encode())
        except BrokenPipeError:
            print(f"Detected broken pipe for {current_conn}")

# Write to UART
def write_line(uart, string):
    for c in string+'\r\n':
        uart.WriteChar(ord(c))

# Global variables to manage state of printing
cleared_line = True
all_received = ''

# Global variables to manage password entry
mach = None
uart = None
entered_password = False

# Global input variables
password = None
instructions_as_delay = None

# Read from UART
def uart_event_read(c):
    global all_received, cleared_line, uart, entered_password, password, mach

    # This limit of 1000 characters is enough to let emulation finish
    # but not let the UART buffer of 1024 chars fill upp
    if len(all_received) > 1000:
        print('Stopping due to 1000 characters printed on UART')
        mach.sysbus.cpu.Pause()

    all_received += chr(c)

    # Print to stdout
    if cleared_line:
        out('[UART]       ', end='')
        cleared_line = False
    else:
        if chr(c) == '\n':
            cleared_line = True
    out(chr(c), end='')

    # Insert the password if prompted to do so
    if not entered_password and 'Enter password: ' in all_received:
        if not cleared_line: out("")
        out(f"[glitcher]   Entering password \"{password}\"")
        cleared_line = True
        write_line(uart, password)
        entered_password = True

# The main function running the emulation for the connected socket
def main():
    global instructions_as_delay, all_received, password, cleared_line, current_conn, uart, entered_password, mach
    
    e = Emulation()
    m = Monitor()

    # Set up the platform
    mach = e.add_mach("stm32f072")
    mach.load_repl("platforms/cpus/stm32f072.repl")
    mach.load_elf("stm32-fw.elf")

    # Enable singlestepping
    mach.sysbus.cpu.ExecutionMode = ExecutionMode.SingleStep

    # Start the emulation
    e.StartAll()
    time.sleep(0.1)

    # Create a saved state to quickly reload for each emulation run
    state_file= "/tmp/state.dat"
    mach.sysbus.cpu.Pause()
    try:
        EmulationManager.Instance.Save(state_file)
        print(f"Save command executed: Save @{state_file}")
    except Exception as e:
        print(f"Error executing save command: {e}")
    mach.sysbus.cpu.Start()

    # Listen to incoming connections
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind((HOST, PORT))
        s.listen()

        # Repeatedly serve connections
        while True:
            # Reset the global printing variables
            cleared_line = True
            all_received = ''

            # Reset the global password entry variables
            uart = None
            entered_password = False

            # Reset the global input variables
            password = None
            instructions_as_delay = None

            conn, addr = s.accept()
            with conn:
                #signal.alarm(10)

                print(f"Connected to {addr} on glitch-emulator service at port {PORT}")
                current_conn = conn
                out("[glitcher]   Connected. Starting up...")

                # Get the input from the relay script
                try:
                    indata = conn.recv(1024).decode()
                    if '\n' in indata:
                        instructions_as_delay = int(indata.split('\n')[0])
                        if len(indata.split('\n')) > 2:
                            password = indata.split('\n')[1].strip()
                        else:
                            password = conn.recv(1024).decode().strip()
                        print(f"{addr} just entered {instructions_as_delay}, {password}")
                    if not instructions_as_delay or not password:
                        conn.close()
                        continue
                except ValueError:
                    out("[glitcher]   Invalid delay or password")
                    out("[glitcher]   Shutting down...")
                    conn.close()
                    continue

                # Load the saved emulation state
                try:
                    EmulationManager.Instance.Load(ReadFilePath(state_file))
                    print(f"Load command executed: Load @{state_file}")
                except Exception as e:
                    print(f"Error executing save command: {e}")
                
                mach = e.get_mach("stm32f072")

                # Catch characters printed on the UART
                uart = list(mach.GetPeripheralsOfType[IUART]())[0]
                uart.CharReceived += uart_event_read

                # Enable singlestepping
                mach.sysbus.cpu.ExecutionMode = ExecutionMode.SingleStep

                # Make the emulation proceed as fast as possible
                mach.sysbus.cpu.AdvanceImmediately = True

                # Start the emulation
                e.StartAll()
                time.sleep(0.1)

                # Wait for the specified number of instructions before injecting the glitch
                mach.sysbus.cpu.Step(instructions_as_delay)

                # Get the current address
                address = mach.sysbus.cpu.PC.get_RawValue()

                # Give some feedback on where the glitch happened
                if not cleared_line: out("")
                out(f"[glitcher]   Executing glitch!")
                out(f"[glitcher]   - Instructions executed: {instructions_as_delay}")
                out(f"[glitcher]   - Current PC: 0x{address:08x}")
                cleared_line = True

                # Skip the instruction
                mach.sysbus.cpu.SetRegisterUnsafe(15, RegisterValue.Create(address+2, 32))
                
                # Continue the execution
                mach.sysbus.cpu.ExecutionMode = ExecutionMode.Continuous

                # Exit
                if not 'Closing terminal...' in all_received:
                    time.sleep(0.2)
                mach.sysbus.cpu.Pause()
                if not cleared_line: out("")
                out("[glitcher]   Shutting down...")
                conn.close()

# Run the main loop but allow for ctrl-C to exit
while True:
    try:
        main()
    except KeyboardInterrupt:
        print("Received KeyboardInterrupt. Exiting...")
