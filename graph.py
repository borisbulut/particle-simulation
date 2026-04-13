import socket
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import rayleigh

HOST = '127.0.0.1'
PORT = 5000

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind((HOST, PORT))
sock.listen(1)

print("Waiting for connection...")
conn, addr = sock.accept()
print("Connected:", addr)

plt.ion()
fig, ax = plt.subplots()

buffer = ""

while True:
    data = conn.recv(4096).decode()
    buffer += data

    # satır bazlı parse
    while "\n" in buffer:
        line, buffer = buffer.split("\n", 1)

        try:
            speeds = np.array([float(x) for x in line.split()])
        except:
            continue

        ax.clear()

        # histogram
        ax.hist(speeds, bins=50, density=True, alpha=0.6)

        # fit (Rayleigh = 2D Maxwell-Boltzmann)
        if len(speeds) > 5:
            sigma = rayleigh.fit(speeds, floc=0)[1]
            x = np.linspace(0, speeds.max(), 200)
            y = rayleigh.pdf(x, scale=sigma)

            ax.plot(x, y, 'r-', lw=2)

        ax.set_title("Velocity Distribution (Real-Time)")
        ax.set_xlabel("Speed")
        ax.set_ylabel("Density")

        plt.pause(0.001)

