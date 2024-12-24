import matplotlib.pyplot as plt
import numpy as np

ris = np.loadtxt ('rappEnergia.txt', unpack = True)

plt.plot (ris[0], ris[1], 'o-', label ='Eulero', color = 'blue')
plt.plot (ris[0], ris[2], 'o-', label = 'Eulero-Cromer', color = 'green')
plt.plot (ris[0], ris[3], 'o-', label = 'Punto Centrale', color = 'red')
plt.plot (ris[0], ris[5], 'o-', label = 'Mezzo Passo', color = 'purple')
plt.grid()
plt.title ('$x_0=2$, $v_0=1$, $w^2=3$, $T=2$')
plt.legend()
plt.xlabel ('dt')
plt.ylabel('(E(T)-E(0))/E(0)')
plt.savefig ('rappEnergia.png', dpi = 1200)
plt.show ()
