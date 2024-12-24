import matplotlib.pyplot as plt
import numpy as np
import sys 

ris = np.loadtxt(sys.argv[1], unpack = True)

plt.plot(ris[0], ris[1], color = 'blue', label = '$\\rho$ = 0.6')
plt.legend()
plt.title ('L = 80')
plt.xlabel ('t')
plt.ylabel ('D(t)')
plt.grid()
plt.savefig("gas.png", dpi=1200)
plt.show()
