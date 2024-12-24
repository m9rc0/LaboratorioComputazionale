import matplotlib.pyplot as plt
import numpy as np

ris = np.loadtxt ('ambiente_aleatorio.txt', unpack = True)

plt.plot (np.log10(ris[0]), ris[1], color = 'red')
plt.xlabel ('log(t)')
plt.ylabel ('$x^2$(t)')
plt.title ('Distanza media su 1000 simulazioni (scala logaritmica)')
plt.grid()
plt.show()
plt.savefig('grafico_x2medio.png')
