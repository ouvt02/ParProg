import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
import sys

points = int(sys.argv[1])
mpl.use('qt5agg')

ref_spec_file = open(f'signals/{points}/reference_spectre.txt', 'r')
spec_file = open(f'signals/{points}/spectre.txt', 'r')

ref_spec = list(map(float, ref_spec_file.read().split()))
spec = list(map(float, spec_file.read().split()))

plt.figure(figsize=[12, 5])
plt.title(f'signals/{points}/reference_spectre.txt')
plt.plot(ref_spec)
plt.savefig(f'signals/{points}/reference_spectre_plot.png')

plt.figure(figsize=[12, 5])
plt.title(f'signals/{points}/spectre.txt')
plt.plot(spec)
plt.savefig(f'signals/{points}/spectre_plot.png')