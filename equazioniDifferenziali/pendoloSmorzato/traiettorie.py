import matplotlib.pyplot as plt
import numpy as np

ris1 = np.loadtxt('smorzamento1.txt', unpack = True)
ris2 = np.loadtxt('smorzamento2.txt', unpack = True)
ris3 = np.loadtxt('smorzamento3.txt', unpack = True)
ris4 = np.loadtxt('smorzamento4.txt', unpack = True)

fig, grafici = plt.subplots(2,2)

fig.suptitle("Traiettorie oscillatore smorzato variando\n il coefficiente di smorzamento")

txt = 'Per il critico si è aggiunta una velocità iniziale negativa per passare una volta per l\'origine'
fig.text(.5, .008, txt, ha='center')


grafici[0][0].plot(ris1[0], ris1[1], color = 'blue')
grafici[0][0].set_xlabel("t")
grafici[0][0].set_ylabel("x(t)")
grafici[0][0].set_title ("Sottosmorzato")
grafici[0][0].grid() 

grafici[1][0].plot(ris2[0], ris2[1], label = '$\Delta t=0.1$ s', color = 'blue')
grafici[1][0].set_xlabel("t")
grafici[1][0].set_ylabel("x(t)")
grafici[1][0].set_title ("Critico (poca energia)")
grafici[1][0].grid()

grafici[0][1].plot(ris4[0], ris4[1], label = '$\Delta t=0.1$ s', color = 'blue')
grafici[0][1].set_xlabel("t")
grafici[0][1].set_ylabel("x(t)")
grafici[0][1].set_title ("Sovrasmorzato")
grafici[0][1].grid()

grafici[1][1].plot(ris3[0], ris3[1], label = '$\Delta t=0.1$ s', color = 'blue')
grafici[1][1].set_xlabel("t")
grafici[1][1].set_ylabel("x(t)")
grafici[1][1].set_title ("Critico (tanta energia)")
grafici[1][1].grid()

fig.tight_layout()

plt.savefig('smorzamento.png', dpi=1200)
plt.show()
