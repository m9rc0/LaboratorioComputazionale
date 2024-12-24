import matplotlib.pyplot as plt
import numpy as np
import sys


ris = [np.loadtxt(sys.argv[i], unpack = True) for i in range(1,3)]
ris = np.array(ris)

fig = plt.figure()

p = []

for i in range(2):
     p.append(fig.add_subplot(1, 2, i+1, projection = '3d'))
     p[i].scatter(ris[i][0], ris[i][1], ris[i][2], s = 0.5)

fig.suptitle('Distribuzioni di probabilità per la posizione a istanti diversi nel tempo')
p[0].set_title('T = 1000')
p[0].azim =50
p[1].set_title('T = 10000')
p[1].azim =50

fig.tight_layout(pad = 2)

plt.savefig('istogrammi2Variables.png', dpi=1200)
plt.show()





