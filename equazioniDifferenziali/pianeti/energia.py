import matplotlib.pyplot as plt
import numpy as np

dati = np.loadtxt ('traiettorie.txt', unpack = True, usecols = (0, 10))
plt.plot(dati[0], dati[1], color = 'red')
plt.xlabel('t')
plt.ylabel('E')
plt.title('Conservazione Energia Meccanica Totale')
plt.grid()
plt.savefig ('energia.png')
plt.show()
