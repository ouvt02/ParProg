import numpy as np
from sys import argv
from os import mkdir

def signal(x_band):
    return np.sin(2 * np.pi * x_band) + np.sin(2000 * np.pi * x_band)

x_band = np.linspace(0, 1, int(argv[1]))
signal_band = signal(x_band)

try: mkdir("signals")
except: pass

try: mkdir(f"signals/{int(argv[1])}/")
except: pass

sig = open(f"signals/{int(argv[1])}/signal.txt", "w")
for s in signal_band:
    sig.write(f"{s:.4f} ")
sig.close()

spe = open(f"signals/{int(argv[1])}/reference_spectre.txt", "w")
spectre_band = np.abs(np.fft.fft(signal_band))
for s in spectre_band:
    spe.write(f"{s:.4f} ")
spe.close()
