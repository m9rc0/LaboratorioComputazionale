import matplotlib.pyplot as plt
import numpy as np

ris = np.loadtxt('pendoloPeriodi.txt', unpack = True)

plt.plot(ris[0], ris[1])
plt.grid()
plt.title('Errore sulla misura del periodo approssimando\n pendolo semplice con oscillatore armonico')
plt.xlabel('$\\theta_0~[^{\circ}]$')
plt.ylabel('$100 \cdot (T - T_{osc})/T$')

plt.savefig('pendoloPeriodi.png', dpi=1200)
plt.show()
