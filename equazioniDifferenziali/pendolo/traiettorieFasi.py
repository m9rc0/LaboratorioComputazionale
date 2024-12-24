import matplotlib.pyplot as plt
import numpy as np

traiettorie = np.loadtxt('traiettorieFasi.txt', unpack = True)



        
for i in range(int(traiettorie.shape[0]/2)):
    plt.scatter(traiettorie[2*i], traiettorie[2*i+1], color = 'Blue', s = 0.01)
#    plt.scatter(traiettorie[2*i][0], traiettorie[2*i+1][0], color = 'Red', s = 5)

plt.ylim([-3 * np.pi, 3 * np.pi])
plt.xlim([-2 * np.pi, 2 * np.pi])

plt.xlabel('x')
plt.ylabel('v')
plt.title('Traiettorie nello spazio delle fasi per pendolo semplice')

theta1 = np.linspace(-np.pi,np.pi,100)
theta2 = np.linspace(-3*np.pi,-np.pi,100)
theta3 = np.linspace(np.pi,3*np.pi,100)
v1 = (2*9.805*(1+np.cos(theta1)))**0.5
v2 = -v1
plt.plot(theta1,v1,color = 'Red', label = 'Traiettorie separatrici')
plt.plot(theta1,v2,color = 'Red')
plt.plot(theta2,v1,color = 'Red')
plt.plot(theta2,v2,color = 'Red')
plt.plot(theta3,v1,color = 'Red')
plt.plot(theta3,v2,color = 'Red')
plt.title('Spazio delle fasi per il pendolo semplice')

#commentare la prossima riga se si vuole vedere solo velocemente l'immagine
#ci mette un po' di tempo a posizionare la legenda
plt.legend()


plt.savefig('traiettorieFasi1.png', dpi = 1200)

plt.show()
