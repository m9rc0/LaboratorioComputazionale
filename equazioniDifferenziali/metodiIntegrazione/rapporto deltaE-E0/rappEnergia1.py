import matplotlib.pyplot as plt
import numpy as np

ris = np.loadtxt ('rappEnergia.txt', unpack = True)
plt.plot (ris[0], ris[2], 'o-', label = 'Eulero-Cromer', color = 'green')
plt.plot (ris[0], ris[4], 'o-', label = 'Verlet-autosufficiente', color = 'blue')
plt.plot (ris[0], ris[6], 'o-', label = 'Predizione-correzione', color = 'red')
plt.grid()
plt.title ('$x_0=2$, $v_0=1$, $w^2=3$, $T=100$')
plt.legend()
plt.xlabel ('dt')
plt.ylabel('(E(T)-E(0))/E(0)')
plt.savefig ('rappEnergia1.png', dpi=1200)
plt.show ()
