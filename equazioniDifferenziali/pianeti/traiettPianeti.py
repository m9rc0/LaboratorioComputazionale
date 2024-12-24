import matplotlib.pyplot as plt
import numpy as np

dati = np.loadtxt ('traiettorie.txt', unpack = True)
plt.plot (0, 0, 'o', color = 'black', label = 'Sole')
plt.plot (-10, 0, 'o', color = 'green')
plt.plot (30.21, 0, 'o', color = 'red')
plt.plot (dati[1], dati[2], color = 'green', label = 'Pianeta 1')
plt.plot (dati[5], dati[6], color = 'red', label = 'Pianeta 2')
plt.suptitle ('Moto di 2 Pianeti')
plt.title ('Condizioni iniziali: $r_1$ = (-10, 0), $r_2$ = (30.21, 0), $v_1$ = (0, -1.5), $v_2$ = (0, -1)')
plt.xlabel ('x(UA)')
plt.ylabel ('y(UA)')
plt.grid()
plt.legend()
plt.savefig ('pianeti.png')
plt.show()
