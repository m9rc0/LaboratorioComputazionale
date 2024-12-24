import matplotlib.pyplot as plt
import numpy as np

ris90 = np.loadtxt('cell90.txt', unpack = True)
ris150 = np.loadtxt('cell150.txt', unpack = True)
ris101 = np.loadtxt('cell101.txt', unpack = True)
ris20 = np.loadtxt('cell20.txt', unpack = True)

fig, [[ax90, ax150], [ax101, ax20]] = plt.subplots(2,2)

ax90.scatter(ris90[0], ris90[1], s = 0.05, color = 'blue')
ax90.set_title('regola 90')
ax90.set_xlabel('x')
ax90.set_ylabel('t')

ax150.scatter(ris150[0], ris150[1], s = 0.05, color = 'blue')
ax150.set_title('regola 150')
ax150.set_xlabel('x')
ax150.set_ylabel('t')


ax101.scatter(ris101[0], ris101[1], s = 0.01, color = 'blue')
ax101.set_title('regola 101')
ax101.set_xlabel('x')
ax101.set_ylabel('t')


ax20.scatter(ris20[0], ris20[1], s = 0.05, color = 'blue')
ax20.set_title('regola 20')
ax20.set_xlabel('x')
ax20.set_ylabel('t')

fig.tight_layout()
plt.savefig('cellAutomaton.png', dpi = 1200)
plt.show()
