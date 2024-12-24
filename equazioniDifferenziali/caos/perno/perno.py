import matplotlib.pyplot as plt
import numpy as np

ris1 = np.loadtxt ('perno.txt', unpack = True)

fig, grafici = plt.subplots(2,3)
fig.suptitle('Spazi delle fasi')

grafici[0][0].scatter(ris1[0], ris1[1], s=0.001)
grafici[0][0].set_title('$g_0 = 1.2$')
grafici[0][0].set_xlabel('x(t)')
grafici[0][0].set_ylabel('v(t)')

grafici[0][1].scatter(ris1[2], ris1[3], s=0.001)
grafici[0][1].set_title('$g_0 = 1.35$')
grafici[0][1].set_xlabel('x(t)')
grafici[0][1].set_ylabel('v(t)')

grafici[0][2].scatter(ris1[4], ris1[5], s=0.001)
grafici[0][2].set_title('$g_0 = 1.40$')
grafici[0][2].set_xlabel('x(t)')
grafici[0][2].set_ylabel('v(t)')

grafici[1][0].scatter(ris1[6], ris1[7], s=0.001)
grafici[1][0].set_title('$g_0 = 1.50$')
grafici[1][0].set_xlabel('x(t)')
grafici[1][0].set_ylabel('v(t)')

grafici[1][1].scatter(ris1[8], ris1[9], s=0.001)
grafici[1][1].set_title('$g_0 = 1.62$')
grafici[1][1].set_xlabel('x(t)')
grafici[1][1].set_ylabel('v(t)')

grafici[1][2].scatter(ris1[10], ris1[11], s=0.001)
grafici[1][2].set_title('$g_0 = 1.75$')
grafici[1][2].set_xlabel('x(t)')
grafici[1][2].set_ylabel('v(t)')


fig.tight_layout()
plt.savefig('perno.png', dpi = 1200)
plt.show()
