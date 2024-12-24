import matplotlib.pyplot as plt
import numpy as np

dati = np.loadtxt ('traiettorie.txt', unpack = True, usecols = (0, 9))
plt.plot(dati[0], dati[1], color = 'green')
plt.xlabel('t')
plt.ylabel('L')
plt.ylim(-0.288, -0.286)
plt.title('Conservazione del Momento Angolare Totale')
plt.grid()
plt.savefig ('momento.png')
plt.show()
