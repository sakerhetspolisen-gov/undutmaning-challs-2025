import sys
import socket
import os
import random
import signal

def handler(signum, frame):
    print("\n[powerglove] Timeout. Shutting down...", flush=True)
    sys.exit(0)

def main():
    # Set timeout for the inputs
    signal.signal(signal.SIGALRM, handler)
    signal.alarm(30)
    print("[IMPORTANT]  Please. Do not spam or script connections!", flush=True)
    
    # Define the address and port
    HOST = "127.0.0.1"
    PORT = 4000 + random.randint(1, int(os.getenv("PARALLEL_RENODE_INSTANCES")))
    
    # Get user input
    delay = input("[powerglove] Enter the delay as number of instructions: ")
    password = input("[powerglove] Enter the password: ")

    # Disable timeout as inputs have been given
    signal.alarm(0)
    
    # Verify inputs
    try:
        delay = int(delay)
        if delay > 100000:
            print("[powerglove] Delay too long. Maximum 100000. Exiting...", flush=True)
            return
    except ValueError:
        print("[powerglove] Invalid delay input. Exiting...", flush=True)
        return
    
    if len(password) > 32:
        print("[powerglove] Password too long. Maximum 32 characters. Exiting...", flush=True)
        return
    
    print("[powerglove] Trying to connect to glitcher module...", flush=True)
    
    # Create socket connection
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        try:
            s.connect((HOST, PORT))
            
            data = s.recv(1024)
            if not 'Connected' in data.decode():
                return
            print(data.decode(), end="", flush=True)

            # Send delay and password
            s.sendall(f"{delay}\n".encode())
            s.sendall(f"{password}\n".encode())
            
            # Read response
            while True:
                data = s.recv(1024)
                if not data:
                    break
                print(data.decode(), end="", flush=True)
                
        except ConnectionRefusedError:
            print("[powerglove] Connection failed. Refused.", flush=True)
        except Exception as e:
            print(f"[powerglove] An error occurred: {e}", flush=True)

        print("[powerglove] Shutting down...", flush=True)
        s.close()

if __name__ == "__main__":
    main()

