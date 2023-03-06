import matplotlib.pyplot as plt
from scipy.interpolate import lagrange
import numpy as np
import math

# open file
f = open("graphe.txt", "r")
name = f.readline()
algo = f.readline()
data = f.read()
f.close()


# split data : [0] = nbSommet, [1] = temps
splitdata = data.rstrip().replace("\n" , ",").split(",")

# get nbSommet
nbSommets = (splitdata[::2])
nbSommets = [item.split("=", 1)[-1] for item in nbSommets]
# print(nbSommets)

# get temps
times = splitdata[1::2]
times = [item.split("=", 1)[-1] for item in times]
# print(times)

x = np.array(nbSommets)
y = np.array(times).astype(float)
# y = np.array(times)

yn = np.power(y, 1/3)
# yn = np.log(y)
# yn = np.exp(yn)
yntmp = np.convolve(yn, np.ones(3), 'valid') / 3
yn = [yn[0]] + list(yntmp) + [yn[-1]]

# poly = lagrange(x, y)
ytmp = np.convolve(y, np.ones(3), 'valid') / 3
y = [y[0]] + list(ytmp) + [y[-1]]

# x = x[1:-1]


# y = [0, 3, 6, 9, 12, 15, 18, 21, 24, 27]

fig, (ax1, ax2) = plt.subplots(1, 2)
if(algo == "no algo\n"):
    fig.suptitle("Temps d'exécution en fonction du nombre de sommets pour un "+name)
else:
    fig.suptitle("Temps d'exécution en fonction du nombre de sommets pour un "+name+algo)


ax1.plot(x, y, color='r', label='Temps d\'exécution')
ax1.legend()

ax2.plot(x, yn, color='b', label='Racine cubique exponentielle de n en temps d\'exécution')
ax2.legend()

ax1.set(xlabel="Nombre de sommets")
ax1.set(ylabel="Temps d'exécution (sec)")

# plt.yscale('log')

# plt.xscale('linear')
plt.show()

