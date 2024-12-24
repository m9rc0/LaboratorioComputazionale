import matplotlib.pyplot as plt
import numpy as np

# si fa il plot per il comportamento attorno al punto di lagrange L4

ris = np.loadtxt("lagrange1.txt", unpack = True)

plt.scatter(ris[0], ris[1], color = 'blue', s= 0.001)
plt.scatter(-1.2151E-2 + 0.5, np.sqrt(3)/2., s=5, color = 'red', label = '$L_1$')
plt.title('Attorno a $L_4$')
plt.legend()
plt.savefig("lagrange1.png", dpi=1200)
