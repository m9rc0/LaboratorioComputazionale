import matplotlib.pyplot as plt
import numpy as np

t10 = np.loadtxt('hist10.txt', unpack = True)
t100 = np.loadtxt('hist100.txt', unpack = True)
t1000 = np.loadtxt('hist1000.txt', unpack = True)
t10000 = np.loadtxt('hist10000.txt', unpack = True)

plt.plot(t10[0], t10[1], label = 'T = 10')
plt.plot(t100[0], t100[1], label = 'T = 100')
plt.plot(t1000[0], t1000[1], label = 'T = 1000')
plt.plot(t10000[0], t10000[1], label = 'T = 10000')

plt.legend()
plt.grid()
plt.title('Distribuzioni di probabilità per la posizione x1 a vari istanti nel tempo')


plt.savefig('istogrammiOneVariable.png', dpi=1200)
plt.show()
