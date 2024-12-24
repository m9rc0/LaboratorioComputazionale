import matplotlib.pyplot as plt
import numpy as np
import sys 

ris = np.loadtxt(sys.argv[1], unpack = True)

for i in range(6):
    plt.plot(ris[2*i], ris[2*i+1], label = '$\\rho$ = ' +str((0.1*(3+i)).round(1)))


    

plt.title ('L = 80')
plt.xlabel ('t')
plt.ylabel ('D(t)')
plt.grid()

plt.legend()
plt.savefig("gasFine.png", dpi=1200)
plt.show()
