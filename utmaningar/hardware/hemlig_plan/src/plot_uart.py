import matplotlib.pyplot as plt 
import sys 
import numpy as np
from pathlib import Path

def read_uart_data(file_path, chunk_size, skip_bytes):
    with open(file_path, "rb") as f:
        f.seek(skip_bytes)
        data = f.read(chunk_size)
    return np.frombuffer(data, dtype=np.uint8)

def plot_uart_waveform(data, sampling_freq, baudrate):
    """Create a screenshot from UART trace
    """
    time = np.linspace(0, len(data) / sampling_freq, len(data))

    plt.figure(figsize=(12,6))
    plt.step(time, data, where='post', linewidth=1.5, color='b')
    plt.ylim(-0.5, 1.5)
    plt.xlabel("Time (s)")
    plt.ylabel("Logic level (0 or 1)")
    plt.title(f"Logic Analyzer viewer \n"
              f"Sampling rate:  {sampling_freq} Hz, Baudrate: {baudrate} baud\n")    
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("buildoutputs/screenshot.png")

if __name__ == "__main__":
    if len(sys.argv) < 5:
        print("Usage: python3 plot_uart.py <sampling_freq> <baud_rate> <chunk_size> <skip_bytes>")
        sys.exit()

    current_dir = Path(__file__).parent
    file_path_in = current_dir / ".." / "buildoutputs" / "captured"
    input_file = file_path_in.resolve()
    sampling_freq = int(sys.argv[1])
    baudrate = int(sys.argv[2])
    chunk_size = int(sys.argv[3])
    skip_bytes = int(sys.argv[4])

    samples_per_bit = int(round(sampling_freq / baudrate))

    data = read_uart_data(input_file, chunk_size, skip_bytes)

    plot_uart_waveform(data, sampling_freq, baudrate)

    