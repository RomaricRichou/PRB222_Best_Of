import csv
import matplotlib.pyplot as plt
import numpy as np


def creer_tableau(cheminfichier, delimiter=";", N=0):
    with open(cheminfichier, 'r', encoding='utf-8') as f:
        rfichier = csv.reader(f, delimiter=delimiter)
        tab = []
        index_row = 0
        for row in rfichier:
            if index_row < N:
                index_row = index_row + 1
            else:
                for i in range(len(row)):
                    # if len(tab) <= i:
                    #     X = []
                    #     tab.append(X)
                    try:
                        tab.append(float(row[i].replace(",", '.')))
                    except ValueError:
                        print('erreur:contenu de cellule non numérique')
                        continue

    return tab


#Affichage Futur = f(nb_sims)
var1 = creer_tableau("varr1.txt", delimiter=";", N=0)
prices1 = creer_tableau("prices1.txt", delimiter=";", N=0)
IC11 = creer_tableau("IC11.txt", delimiter=";", N=0)
IC21 = creer_tableau("IC21.txt", delimiter=";", N=0)
nb_sims = creer_tableau("nb_sims.txt", delimiter=";", N=0)
print("nbsims=", nb_sims)
print("prices1=", prices1)

plt.plot(np.log10(nb_sims), prices1, 'r', label='prices=f(log(nb_sims))')
plt.plot(np.log10(nb_sims), IC11, '--r', label='IC1=f(log(nb_sims))')
plt.plot(np.log10(nb_sims), IC21, '--r', label='IC2=f(log(nb_sims))')
plt.legend()
plt.title("Futur = f(nb_sims)")
plt.show()

#Affichage Futur = f(rho)
var2 = creer_tableau("varr2.txt", delimiter=";", N=0)
rho = creer_tableau("rho.txt", delimiter=";", N=0)
prices2 = creer_tableau("prices2.txt", delimiter=";", N=0)
IC12 = creer_tableau("IC12.txt", delimiter=";", N=0)
IC22 = creer_tableau("IC22.txt", delimiter=";", N=0)
print("rho=", rho)
print("prices2=", prices2)

plt.plot(rho, prices2, 'r', label='prices=f(rho)')
plt.plot(rho, IC12, '--r', label='IC1=f(rho)')
plt.plot(rho, IC22, '--r', label='IC2=f(rho)')
plt.legend()
plt.title("Futur = f(rho)")
plt.show()

#Affichage Put = f(nb_sims)
var3 = creer_tableau("varr3.txt", delimiter=";", N=0)
prices3 = creer_tableau("prices3.txt", delimiter=";", N=0)
IC13 = creer_tableau("IC13.txt", delimiter=";", N=0)
IC23 = creer_tableau("IC23.txt", delimiter=";", N=0)
print("nbsims=", nb_sims)
print("prices3=", prices3)

plt.plot(np.log(nb_sims), prices3, 'r', label='prices=f(log(nb_sims))')
plt.plot(np.log(nb_sims), IC13, '--r', label='IC1=f(log(nb_sims))')
plt.plot(np.log(nb_sims), IC23, '--r', label='IC2=f(log(nb_sims))')
plt.legend()
plt.title("Put = f(nb_sims)")
plt.show()

#Affichage Futur = f(rho)
var4 = creer_tableau("varr4.txt", delimiter=";", N=0)
prices4 = creer_tableau("prices4.txt", delimiter=";", N=0)
IC14 = creer_tableau("IC14.txt", delimiter=";", N=0)
IC24 = creer_tableau("IC24.txt", delimiter=";", N=0)
ctrl = creer_tableau("ctrl.txt", delimiter=";", N=0)
print("rho=", rho)
print("prices4=", prices4)

plt.plot(rho, prices4, 'r', label='prices=f(rho)')
plt.plot(rho, ctrl, '--b', label='prix du put européen')
plt.plot(rho, IC14, '--r', label='IC1=f(rho)')
plt.plot(rho, IC24, '--r', label='IC2=f(rho)')
plt.legend()
plt.title("Put = f(rho)")
plt.show()