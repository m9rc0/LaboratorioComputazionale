import matplotlib.pyplot as plt
import numpy as np

ris = np.loadtxt("rumore.txt", unpack = True)

fig, grafici = plt.subplots(2,1)

fig.suptitle('Eulero e Eulero-Cromer con rumore (utilizzando solo 2 cifre decimali nei calcoli interni)', fontsize = 10)
txt = 'T = 20, $\omega^2$ = 3, x0=2, v0=0, dt = 0.01'
fig.text(.5, .002, txt, ha='center')


grafici[0].plot(ris[0], ris[1], color = 'blue', label = 'no rumore')
grafici[0].plot(ris[0], ris[2], color = 'red', label = 'rumore')
grafici[0].grid()
grafici[0].legend()
grafici[0].set_xlabel('t')
grafici[0].set_ylabel('$(E-E_0)/E0$')
grafici[0].set_title("Eulero")

grafici[1].plot(ris[0], ris[3], color = 'blue', label = 'no rumore')
grafici[1].plot(ris[0], ris[4], color = 'red', label = 'rumore')
grafici[1].grid()
grafici[1].set_xlabel('t')
grafici[1].set_ylabel('$(E-E_0)/E0$')
grafici[1].set_title("Eulero-Cromer")

fig.tight_layout()
plt.savefig("rumore.png", dpi=1200)
plt.show()
