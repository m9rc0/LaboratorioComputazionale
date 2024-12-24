import matplotlib.pyplot as plt
import numpy as np

# si fa il plot per il comportamento attorno al punto di lagrange L1, a destra o a sinistra

ris1 = np.loadtxt("lagrange3.txt", unpack = True)
ris2 = np.loadtxt("lagrange4.txt", unpack = True)

plt.scatter(ris1[0], ris1[1], color = 'blue', s= 0.001)
plt.scatter(ris2[0], ris2[1], color = 'orange', s= 0.001)
plt.scatter(0.836915, 0, s=5, color = 'red', label = '$L_1$')
plt.scatter(-0.012151, 0, s=5, color = 'purple', label = '$m_1$')
plt.scatter(1-0.012151, 0, s=5, color = 'green', label = '$m_2$')
plt.title('Attorno a $L_1$\nIn blu orbita a sinistra, in giallo orbita a destra.')

plt.legend()

plt.savefig("lagrange2.png", dpi=1200)
