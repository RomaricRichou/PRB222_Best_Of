import csv
import matplotlib.pyplot as plt
import numpy as np

def creer_tableau(cheminfichier, delimiter=";",N=0):
    with open(cheminfichier, 'r', encoding='utf-8') as f :
        rfichier = csv.reader(f, delimiter=delimiter)
        tab=[]
        index_row=0
        for row in rfichier:
            if index_row < N:
                index_row = index_row+1
            else :
                for i in range (len(row)):
                    # if len(tab) <= i:
                    #     X = []
                    #     tab.append(X)
                    try:
                        tab.append(float(row[i].replace(",",'.')))
                    except ValueError:
                        print('erreur:contenu de cellule non numérique')
                        continue
    

    return tab

var2=creer_tableau("varr2.txt",delimiter=";",N=0)
rho=creer_tableau("rho.txt",delimiter=";",N=0)
prices=creer_tableau("prices.txt",delimiter=";",N=0)
prices2=creer_tableau("prices2.txt",delimiter=";",N=0)

IC1=creer_tableau("IC12.txt",delimiter=";",N=0)
IC2=creer_tableau("IC22.txt",delimiter=";",N=0)
nb_sims=creer_tableau("nb_sims.txt",delimiter=";",N=0)
err2=creer_tableau("err2.txt",delimiter=";",N=0)

print("nbsims=",nb_sims)
print("prices2=",prices)

# plt.plot(nb_sims,prices,'r',label='prix forward avec min-var=f(nb_sims))')
# plt.plot(nb_sims,IC1,'g+',label='IC1=f(nb_sims)')
# plt.plot(nb_sims,IC2,'r+',label='IC2=f(nb_sims)')
plt.plot(rho,prices,'r',label='prix forward call avec min-var=f(rho)')

plt.legend()
plt.xlabel("rho")
plt.ylabel("Prix forward call avec min-var")
plt.show()
#plt.plot(t,y,'r+',label='y=g(x)')
# plt.legend()
# plt.xlabel("t (s)")
# plt.ylabel("x(m) et y(m)")
# plt.grid()
# plt.title("Evolution des coordonnées au cours d'un mouvement parabolique")
