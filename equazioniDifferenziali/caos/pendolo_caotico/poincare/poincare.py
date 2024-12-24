import matplotlib.pyplot as plt
import numpy as np

ris1 = np.loadtxt ('poincare.txt', unpack = True)

fig, grafici = plt.subplots(2,3)
fig.suptitle('Sezioni di poincare')

grafici[0][0].scatter(ris1[0], ris1[1], s=0.5)
grafici[0][0].set_title('$f_0 = 0.9$')
grafici[0][0].set_xlabel('x(t)')
grafici[0][0].set_ylabel('v(t)')

grafici[0][1].scatter(ris1[2], ris1[3], s=0.5)
grafici[0][1].set_title('$f_0 = 1.07$')
grafici[0][1].set_xlabel('x(t)')
grafici[0][1].set_ylabel('v(t)')

grafici[0][2].scatter(ris1[4], ris1[5], s=0.5)
grafici[0][2].set_title('$f_0 = 1.15$')
grafici[0][2].set_xlabel('x(t)')
grafici[0][2].set_ylabel('v(t)')

grafici[1][0].scatter(ris1[6], ris1[7], s=0.5)
grafici[1][0].set_title('$f_0 = 1.35$')
grafici[1][0].set_xlabel('x(t)')
grafici[1][0].set_ylabel('v(t)')

grafici[1][1].scatter(ris1[8], ris1[9], s=0.5)
grafici[1][1].set_title('$f_0 = 1.47$')
grafici[1][1].set_xlabel('x(t)')
grafici[1][1].set_ylabel('v(t)')

grafici[1][2].scatter(ris1[10], ris1[11], s=0.5)
grafici[1][2].set_title('$f_0 = 1.50$')
grafici[1][2].set_xlabel('x(t)')
grafici[1][2].set_ylabel('v(t)')


fig.tight_layout()
plt.savefig('poincare.png', dpi = 1200)
plt.show()
