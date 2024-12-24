import matplotlib.pyplot as plt
import numpy as np

# si fa il plot per il comportamento attorno al punto di lagrange L2, a sinistra

ris1 = np.loadtxt("lagrange6.txt", unpack = True)


plt.scatter(ris1[0], ris1[1], color = 'blue', s= 0.001)
plt.scatter(1.15568, 0, s=5, color = 'red', label = '$L_2$')
plt.title('Attorno a $L_2$')
plt.scatter(-0.012151, 0, s=5, color = 'purple', label = '$m_1$')
plt.scatter(1-0.012151, 0, s=5, color = 'green', label = '$m_2$')

plt.legend()

plt.savefig("lagrange3.png", dpi=1200)
