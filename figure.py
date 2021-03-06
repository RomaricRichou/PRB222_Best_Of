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
                        print('erreur:contenu de cellule non numérique',cheminfichier)
                        continue

    return tab


#Affichage Futur = f(nb_sims)
var1 = creer_tableau("varr1.txt", delimiter=";", N=0)
prices1 = creer_tableau("prices1.txt", delimiter=";", N=0)
IC11 = creer_tableau("IC11.txt", delimiter=";", N=0)
IC21 = creer_tableau("IC21.txt", delimiter=";", N=0)
nb_sims = creer_tableau("nb_sims.txt", delimiter=";", N=0)
err1 = creer_tableau("err1.txt", delimiter=";", N=0)
print("nbsims=", nb_sims)
print("prices1=", prices1)

plt.plot(nb_sims, prices1, 'r', label='prices=f(nb_sims)')
plt.plot(nb_sims, IC11, '--r', label='IC1=f(nb_sims)')
plt.plot(nb_sims, IC21, '--r', label='IC2=f(nb_sims)')
plt.legend()
plt.title("Forward = f(nb_sims)")
plt.show()

#Affichage Erreur = f(nb_sim)
plt.plot(nb_sims, err1, 'r', label='err=f(nb_sims)')
plt.legend()
plt.title("Erreur Forward = f(nb_sims)")
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
plt.title("Forward = f(rho)")
plt.show()

#Affichage Put = f(nb_sims)
var3 = creer_tableau("varr3.txt", delimiter=";", N=0)
prices3 = creer_tableau("prices3.txt", delimiter=";", N=0)
IC13 = creer_tableau("IC13.txt", delimiter=";", N=0)
IC23 = creer_tableau("IC23.txt", delimiter=";", N=0)
err3 = creer_tableau("err3.txt", delimiter=";", N=0)
print("nbsims=", nb_sims)
print("prices3=", prices3)

plt.plot(nb_sims, prices3, 'r', label='prices=f(nb_sims)')
plt.plot(nb_sims, IC13, '--r', label='IC1=f(nb_sims)')
plt.plot(nb_sims, IC23, '--r', label='IC2=f(nb_sims)')
plt.legend()
plt.title("Put = f(nb_sims)")
plt.show()

#Affichage Erreur put = f(nb_sim)
plt.plot(nb_sims, err3, 'r', label='err=f(nb_sims)')
plt.legend()
plt.title("Erreur put = f(nb_sims)")
plt.show()

#Affichage Put = f(rho)
var4 = creer_tableau("varr4.txt", delimiter=";", N=0)
prices4 = creer_tableau("prices4.txt", delimiter=";", N=0)
IC14 = creer_tableau("IC14.txt", delimiter=";", N=0)
IC24 = creer_tableau("IC24.txt", delimiter=";", N=0)
ctrl = creer_tableau("ctrl.txt", delimiter=";", N=0)
err4 = creer_tableau("err4.txt", delimiter=";", N=0)

var5 = creer_tableau("varr5.txt", delimiter=";", N=0)
prices5 = creer_tableau("prices5.txt", delimiter=";", N=0)
IC15 = creer_tableau("IC15.txt", delimiter=";", N=0)
IC25 = creer_tableau("IC25.txt", delimiter=";", N=0)
err5 = creer_tableau("err5.txt", delimiter=";", N=0)
print("rho=", rho)
print("prices4=", prices4)

plt.plot(rho, prices4, 'r', label='prices=f(rho) pour K=1')
plt.plot(rho, IC14, '--r', label='IC1=f(rho)')
plt.plot(rho, IC24, '--r', label='IC2=f(rho)')
plt.plot(rho, ctrl, '--b', label='prix du put européen')

plt.legend()
plt.title("Put = f(rho)")
plt.show()

#Affichage erreur des deux méthodes en fonction de rho
plt.plot(rho,err4,'r',label='Erreur')
plt.plot(rho,err5,'g',label='Erreur avec variable de controle')
plt.title('Erreur = f(rho)')
plt.legend()
plt.show()

#Affichage bestof put et put en fonction de S10
var6 = creer_tableau("varr6.txt", delimiter=";", N=0)
prices6 = creer_tableau("prices6.txt", delimiter=";", N=0)
IC16 = creer_tableau("IC16.txt", delimiter=";", N=0)
IC26 = creer_tableau("IC26.txt", delimiter=";", N=0)
prices7 = creer_tableau("prices7.txt", delimiter=";", N=0)
err6 = creer_tableau("err6.txt", delimiter=";", N=0)
S10 = creer_tableau("S10.txt", delimiter=";", N=0)

plt.plot(S10,prices6,'r',label='bestof put = f(S10)')
plt.plot(S10,IC16,'--r',label='IC1')
plt.plot(S10,IC26,'--r',label='IC2')
plt.plot(S10,prices7,'g',label='Put sur un seul actif')
plt.title("Affichage bestof put et put en fonction de S10")
plt.legend()
plt.show()

#Affichage du prix en fonction de N
prices_rho1 = creer_tableau("prices_rho1.txt", delimiter=";", N=0)
prices_rho2 = creer_tableau("prices_rho2.txt", delimiter=";", N=0)
prices_rho3 = creer_tableau("prices_rho3.txt", delimiter=";", N=0)
N = creer_tableau("N.txt", delimiter=";", N=0)

plt.plot(N, prices_rho1, 'or--', label='prices_rho1=f(N)')
plt.plot(N, prices_rho2, 'og--', label='prices_rho2=f(N)')
plt.plot(N, prices_rho3, 'ob--', label='prices_rho3=f(N)')
plt.legend()
plt.show()


