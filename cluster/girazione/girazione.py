import matplotlib.pyplot as plt
import numpy as np

ris = np.loadtxt('girazione.txt', unpack = True)

plt.scatter (ris[0], ris[1], color = 'red', s = 15, label = 'Valori  di R')
plt.xlabel ('Probabilità p')
plt.ylabel ('Raggio di girazione R')
plt.title ('Raggio di girazione vs probabilità')
plt.axvline (0.593, 0, 20)
plt.grid()
plt.legend()
plt.savefig('girazione.png', dpi = 1200)
plt.show()
