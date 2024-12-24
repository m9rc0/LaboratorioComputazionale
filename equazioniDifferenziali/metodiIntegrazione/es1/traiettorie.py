import matplotlib.pyplot as plt
import numpy as np

ris1 = np.loadtxt('traiettorie1.txt', unpack = True)
ris2 = np.loadtxt('traiettorie2.txt', unpack = True)
ris3 = np.loadtxt('traiettorie3.txt', unpack = True)

fig, grafici = plt.subplots(2,2)

fig.tight_layout()

grafici[0][0].plot(ris1[0], ris1[1], label = '$\Delta t=0.1$ s', color = 'blue')
grafici[0][0].plot(ris2[0], ris2[1], label = '$\Delta t=0.01$ s', color = 'red')
grafici[0][0].plot(ris3[0], ris3[1], label = '$\Delta t=0.001$ s', color = 'green')
grafici[0][0].set_xlabel("t")
grafici[0][0].set_ylabel("x(t)")
grafici[0][0].set_title ("Eulero")

grafici[1][0].plot(ris1[0], ris1[3], label = '$\Delta t=0.1$ s', color = 'blue')
grafici[1][0].plot(ris2[0], ris2[3], label = '$\Delta t=0.01$ s', color = 'red')
grafici[1][0].plot(ris3[0], ris3[3], label = '$\Delta t=0.001$ s', color = 'green')
grafici[1][0].set_xlabel("t")
grafici[1][0].set_ylabel("x(t)")
grafici[1][0].set_title ("Eulero-Cromer")

grafici[0][1].plot(ris1[0], ris1[5], label = '$\Delta t=0.1$ s', color = 'blue')
grafici[0][1].plot(ris2[0], ris2[5], label = '$\Delta t=0.01$ s', color = 'red')
grafici[0][1].plot(ris3[0], ris3[5], label = '$\Delta t=0.001$ s', color = 'green')
grafici[1][0].legend()
grafici[0][1].set_xlabel("t")
grafici[0][1].set_ylabel("x(t)")
grafici[0][1].set_title ("Punto Centrale")

grafici[1][1].plot(ris1[0], ris1[7], label = '$\Delta t=0.1$ s', color = 'blue')
grafici[1][1].plot(ris2[0], ris2[7], label = '$\Delta t=0.01$ s', color = 'red')
grafici[1][1].plot(ris3[0], ris3[7], label = '$\Delta t=0.001$ s', color = 'green')
grafici[1][1].set_xlabel("t")
grafici[1][1].set_ylabel("x(t)")
grafici[1][1].set_title ("Mezzo Passo")

fig.tight_layout()

plt.savefig('traiettorie.png', dpi=1200)
plt.show()
