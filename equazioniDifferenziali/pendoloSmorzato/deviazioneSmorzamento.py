import matplotlib.pyplot as plt
import numpy as np

ris = np.loadtxt("deviazioneSmorzamento.txt", unpack = True)

plt.plot(ris[0], ris[1])

plt.title("Andamento deviazione standard interpolando con le rette\nin funzione di gamma")

plt.xlabel("$\gamma$")
plt.ylabel("$\sigma$")
plt.grid()

plt.savefig("deviazioneSmorzamento.png", dpi=1200)
plt.show()
