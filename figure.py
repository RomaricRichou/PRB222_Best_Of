import csv
import matplotlib.pyplot as plt
import numpy as np

def show_figure(cheminfichier, delimiter=";",N=0):
    with open(cheminfichier, 'r', encoding='utf-8') as f :
        rfichier = csv.reader(f, delimiter=delimiter)
        tab=[]
        index_row=0
        for row in rfichier:
            if index_row < N:
                index_row = index_row+1
            else :
                for i in range (len(row)):
                    if len(tab) <= i:
                        X = []
                        tab.append(X)
                    try:
                        tab[i].append(float(row[i].replace(",",'.')))
                    except ValueError:
                        print('erreur:contenu de cellule non numérique')
                        continue
    

    return tab

vect_global=sh