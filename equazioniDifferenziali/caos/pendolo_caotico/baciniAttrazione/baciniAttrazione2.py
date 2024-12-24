import matplotlib.pyplot as plt
import numpy as np
import sys

nero1 = np.loadtxt('nero1.txt', unpack = True)
giallo1 = np.loadtxt('giallo1.txt', unpack = True)

nero2 = np.loadtxt('nero2.txt', unpack = True)
giallo2 = np.loadtxt('giallo2.txt', unpack = True)

nero3 = np.loadtxt('nero3.txt', unpack = True)
giallo3 = np.loadtxt('giallo3.txt', unpack = True)

nero4 = np.loadtxt('nero4.txt', unpack = True)
giallo4 = np.loadtxt('giallo4.txt', unpack = True)


fig, grafici = plt.subplots(2,2)

if nero1.size != 0:
    grafici[0][0].scatter(nero1[0], nero1[1], color = 'black', s=0.01)
if giallo1.size !=0:
    grafici[0][0].scatter(giallo1[0], giallo1[1], color = 'yellow', s=0.01)
grafici[0][0].set_title("T = "+ sys.argv[1]+"s")
grafici[0][0].set_box_aspect(0.7)
# grafici[0][0].set_xlabel("x0")
# grafici[0][0].set_ylabel("v0")
    
if nero2.size != 0:
    grafici[0][1].scatter(nero2[0], nero2[1], color = 'black', s=0.01)
if giallo2.size != 0:
    grafici[0][1].scatter(giallo2[0], giallo2[1], color = 'yellow', s=0.01)
grafici[0][1].set_title("T = "+ sys.argv[2]+"s")
grafici[0][1].set_box_aspect(0.7)
# grafici[0][1].set_xlabel("x0")
# grafici[0][1].set_ylabel("v0")


if nero3.size != 0:
    grafici[1][0].scatter(nero3[0], nero3[1], color = 'black', s=0.01)
if giallo3.size != 0:
    grafici[1][0].scatter(giallo3[0], giallo3[1], color = 'yellow', s=0.01)
grafici[1][0].set_title("T = "+ sys.argv[3]+"s")
grafici[1][0].set_box_aspect(0.7)
# grafici[1][0].set_xlabel("x0")
# grafici[1][0].set_ylabel("v0")


if nero4.size != 0:
    grafici[1][1].scatter(nero4[0], nero4[1], color = 'black', s=0.01)
if giallo4.size != 0:
    grafici[1][1].scatter(giallo4[0], giallo4[1], color = 'yellow', s=0.01)
grafici[1][1].set_title("T = "+ sys.argv[4]+"s")
grafici[1][1].set_box_aspect(0.7)
# grafici[1][1].set_xlabel("x0")
# grafici[1][1].set_ylabel("v0")


fig.suptitle("Andamento bacini di attrazione nel tempo \n($\omega = 1, \\bar{\omega}=2/3, \gamma = 0.5, x_0 = \pi/2, v_0 = 0$)")

fig.tight_layout()

plt.savefig('baciniAttrazione2.png', dpi=1200)
plt.show()
