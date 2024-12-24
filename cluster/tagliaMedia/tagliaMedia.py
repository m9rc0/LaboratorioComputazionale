import matplotlib.pyplot as plt
import numpy as np

ris = np.loadtxt('tagliaMedia.txt', unpack = True)

plt.scatter(ris[0], ris[1], color = 'blue', s=0.5)
plt.title('Taglia media cluster in funzione di p, L = 150')
plt.xlabel('p')
plt.ylabel('T')
plt.grid()
plt.savefig('tagliaMedia.png', dpi=1200)
plt.show()

