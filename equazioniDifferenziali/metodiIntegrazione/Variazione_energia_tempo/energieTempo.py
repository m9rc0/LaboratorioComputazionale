import matplotlib.pyplot as plt
import numpy as np

ris1 = np.loadtxt('energieTempo1.txt', unpack = True)
ris2 = np.loadtxt('energieTempo2.txt', unpack = True)
ris3 = np.loadtxt('energieTempo3.txt', unpack = True)

fig, grafici = plt.subplots(2,2)

grafici[0][0].plot(ris1[0], ris1[1], label = '$\Delta t=0.1$ s', color = 'blue')
grafici[0][0].plot(ris2[0], ris2[1], label = '$\Delta t=0.01$ s', color = 'red')
grafici[0][0].plot(ris3[0], ris3[1], label = '$\Delta t=0.001$ s', color = 'green')
grafici[0][0].set_xlabel("t")
grafici[0][0].set_ylabel("$(E_0-E)/E_0$")
grafici[0][0].set_title ("Eulero")
grafici[0][0].set_ylim([-20,10])
grafici[0][0].grid()

grafici[1][0].plot(ris1[0], ris1[2], label = '$\Delta t=0.1$ s', color = 'blue')
grafici[1][0].plot(ris2[0], ris2[2], label = '$\Delta t=0.01$ s', color = 'red')
grafici[1][0].plot(ris3[0], ris3[2], label = '$\Delta t=0.001$ s', color = 'green')
grafici[1][0].set_xlabel("t")
grafici[1][0].set_ylabel("$(E_0-E)/E_0$")
grafici[1][0].set_title ("Eulero-Cromer")
grafici[1][0].grid()

grafici[0][1].plot(ris1[0], ris1[3], label = '$\Delta t=0.1$ s', color = 'blue')
grafici[0][1].plot(ris2[0], ris2[3], label = '$\Delta t=0.01$ s', color = 'red')
grafici[0][1].plot(ris3[0], ris3[3], label = '$\Delta t=0.001$ s', color = 'green')
grafici[1][0].legend()
grafici[0][1].set_xlabel("t")
grafici[0][1].set_ylabel("$(E_0-E)/E_0$")
grafici[0][1].set_title ("Punto Centrale")
grafici[0][1].set_ylim([-20,10])
grafici[0][1].grid()

grafici[1][1].plot(ris1[0], ris1[4], label = '$\Delta t=0.1$ s', color = 'blue')
grafici[1][1].plot(ris2[0], ris2[4], label = '$\Delta t=0.01$ s', color = 'red')
grafici[1][1].plot(ris3[0], ris3[4], label = '$\Delta t=0.001$ s', color = 'green')
grafici[1][1].set_xlabel("t")
grafici[1][1].set_ylabel("$(E_0-E)/E_0$")
grafici[1][1].set_title ("Mezzo Passo")
grafici[1][1].grid()

fig.suptitle("Variazione dell'energia meccanica in funzione del tempo")
fig.tight_layout()


plt.savefig('energieTempo.png', dpi=1200)
plt.show()
