import matplotlib.pyplot as plt
import numpy as np

dati = np.loadtxt ('biforc.txt', unpack = True)

plt.scatter (dati[0], dati[1], s = 0.05)
plt.title ('Diagrammi di biforcazione del pendolo con perno mobile')
plt.xlabel ('$g_0$')
plt.ylabel ('v')
plt.savefig ('biforc.png', dpi = 1200)
plt.show()
