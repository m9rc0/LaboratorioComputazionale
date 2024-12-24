import matplotlib.pyplot as plt
import numpy as np


ris1 = np.loadtxt('treCorpi1.txt', unpack = True)
ris2 = np.loadtxt('treCorpi2.txt', unpack = True)
ris3 = np.loadtxt('treCorpi3.txt', unpack = True)
ris4 = np.loadtxt('treCorpi4.txt', unpack = True)

fig, grafici = plt.subplots(2,2)

fig.tight_layout()

grafici[0][0].scatter(ris1[0], ris1[1], s = 0.01, color = 'blue')
grafici[0][0].scatter(ris1[2], ris1[3], s = 0.01, color = 'red')
grafici[0][0].scatter(ris1[4], ris1[5], s = 0.01, color = 'green')
grafici[0][0].set_xlabel("X")
grafici[0][0].set_ylabel("Y")
grafici[0][0].set_box_aspect(1)
#grafici[0][0].set_title ("Eulero")

grafici[0][1].scatter(ris2[0], ris2[1], s = 0.01, color = 'blue')
grafici[0][1].scatter(ris2[2], ris2[3], s = 0.01, color = 'red')
grafici[0][1].scatter(ris2[4], ris2[5], s = 0.01, color = 'green')
grafici[0][1].set_xlabel("X")
grafici[0][1].set_ylabel("Y")
grafici[0][1].set_box_aspect(1)

grafici[1][0].scatter(ris3[0], ris3[1], s = 0.01, color = 'blue')
grafici[1][0].scatter(ris3[2], ris3[3], s = 0.01, color = 'red')
grafici[1][0].scatter(ris3[4], ris3[5], s = 0.01, color = 'green')
grafici[1][0].set_xlabel("X")
grafici[1][0].set_ylabel("Y")
grafici[1][0].set_xlim([-1,1])
grafici[1][0].set_ylim([-1,1])
grafici[1][0].set_box_aspect(1)


grafici[1][1].scatter(ris4[0], ris4[1], s = 0.01, color = 'blue')
grafici[1][1].scatter(ris4[2], ris4[3], s = 0.01, color = 'red')
grafici[1][1].scatter(ris4[4], ris4[5], s = 0.01, color = 'green')
grafici[1][1].set_xlabel("X")
grafici[1][1].set_ylabel("Y")
grafici[1][1].set_box_aspect(1)

fig.tight_layout()

plt.savefig('treCorpi.png', dpi=1200)
plt.show() 
