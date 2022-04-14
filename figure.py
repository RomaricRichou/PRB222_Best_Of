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
nb_sims = creer_tableau("nb_sims1.txt", delimiter=";", N=0)
print("nbsims=", nb_sims)
print("prices1=", prices1)

plt.plot(np.log(nb_sims), prices1, 'b', label='prices1=f(nb_sims)')
plt.plot(np.log(nb_sims), IC11, 'g', label='IC11=f(nb_sims)')
plt.plot(np.log(nb_sims), IC21, 'r', label='IC21=f(nb_sims)')
plt.legend("Futur = f(nb_sims)")
plt.show()

#Affichage Futur = f(rho)
var2 = creer_tableau("varr2.txt", delimiter=";", N=0)
rho = creer_tableau("rho.txt", delimiter=";", N=0)
prices2 = creer_tableau("prices2.txt", delimiter=";", N=0)
IC12 = creer_tableau("IC12.txt", delimiter=";", N=0)
IC22 = creer_tableau("IC22.txt", delimiter=";", N=0)
print("rho=", rho)
print("prices2=", prices2)

plt.plot(rho, prices2, 'b', label='prices1=f(nb_sims)')
plt.plot(rho, IC12, 'g', label='IC12=f(nb_sims)')
plt.plot(rho, IC22, 'r', label='IC22=f(nb_sims)')
plt.legend("Futur = f(rho)")
plt.show()

#Affichage Put = f(nb_sims)
var3 = creer_tableau("varr3.txt", delimiter=";", N=0)
prices3 = creer_tableau("prices3.txt", delimiter=";", N=0)
IC13 = creer_tableau("IC13.txt", delimiter=";", N=0)
IC23 = creer_tableau("IC23.txt", delimiter=";", N=0)
print("nbsims=", nb_sims)
print("prices1=", prices3)

plt.plot(np.log(nb_sims), prices1, 'b', label='prices1=f(nb_sims)')
plt.plot(np.log(nb_sims), IC11, 'g', label='IC11=f(nb_sims)')
plt.plot(np.log(nb_sims), IC21, 'r', label='IC21=f(nb_sims)')
plt.legend("Futur = f(nb_sims)")
plt.show()

#Affichage Futur = f(rho)
var2 = creer_tableau("varr2.txt", delimiter=";", N=0)
rho = creer_tableau("rho.txt", delimiter=";", N=0)
prices2 = creer_tableau("prices2.txt", delimiter=";", N=0)
IC12 = creer_tableau("IC12.txt", delimiter=";", N=0)
IC22 = creer_tableau("IC22.txt", delimiter=";", N=0)
print("rho=", rho)
print("prices2=", prices2)

plt.plot(rho, prices2, 'b', label='prices1=f(nb_sims)')
plt.plot(rho, IC12, 'g', label='IC12=f(nb_sims)')
plt.plot(rho, IC22, 'r', label='IC22=f(nb_sims)')
plt.legend("Futur = f(rho)")
plt.show()