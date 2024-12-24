import matplotlib.pyplot as plt
import numpy as np

ris = np.loadtxt("bifurcationPendolo.txt", unpack = True)

plt.scatter(ris[0], ris[1], s=0.1, color = 'blue')

plt.axvline(1.07, linestyle = '--', color = 'red', linewidth = 0.8, label = '$f_0 = 1,07$')
plt.axvline(1.50, linestyle = '--', color = 'green', linewidth = 0.8, label = '$f_0 = 1.50$')

plt.xlabel('$f_0$')
plt.ylabel('$v(k \cdot T)$')

plt.legend()

plt.title('Diagramma di biforzazione per pendolo caotico\n($\omega = 1, \\bar{\omega}=2/3, \gamma = 0.5, x_0 = \pi/2, v_0 = 0$)')

plt.savefig("bifurcationPendolo.png", dpi = 1200)
plt.show()
