import matplotlib.pyplot as plt
import numpy as np


ris1 = np.loadtxt('traiettorie2.txt', unpack = True)


fig, grafici = plt.subplots(2,2)
fig.suptitle('Spazi delle fasi')

grafici[0][0].plot(ris1[1], ris1[2], linewidth = 0.5)
grafici[0][0].set_title('Eulero')
grafici[0][0].set_xlabel('x(t)')
grafici[0][0].set_ylabel('v(t)')

grafici[0][1].plot(ris1[3], ris1[4], linewidth = 0.5)
grafici[0][1].set_title('Cromer')
grafici[0][1].set_xlabel('x(t)')
grafici[0][1].set_ylabel('v(t)')

grafici[1][0].plot(ris1[5], ris1[6], linewidth = 0.5)
grafici[1][0].set_title('Punto Centrale')
grafici[1][0].set_xlabel('x(t)')
grafici[1][0].set_ylabel('v(t)')

grafici[1][1].plot(ris1[7], ris1[8], linewidth = 0.5)
grafici[1][1].set_title('Mezzo Passo')
grafici[1][1].set_xlabel('x(t)')
grafici[1][1].set_ylabel('v(t)')

fig.tight_layout()
plt.savefig('fasi.png', dpi = 1200)
plt.show()
