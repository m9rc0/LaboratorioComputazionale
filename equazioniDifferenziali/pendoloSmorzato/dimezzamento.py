import matplotlib.pyplot as plt
import numpy as np

ris = np.loadtxt("dimezzamento.txt", unpack = True)

plt.plot(ris[0],'o-')
plt.title('Linearità tempi per successivi dimezzamenti')
plt.grid()
plt.xlabel("$N^{\circ}$ dimezzamenti")
plt.ylabel('$\\tau$')

plt.savefig("dimezzamenti.png", dpi=1200)
plt.show()
