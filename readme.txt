Le fichier fonctions.hpp contient les definitions de toutes les fonctions implémentées dans fonctions.cpp
Les fichiers Matrice contiennent les fonctionnalités nécessaires pour créer des matrices.

Dans le main, on génére automatiquement les résultats des questions dans l'ordre, l'exécution se fait en créeant les fichiers .txt nécessaires pour tracer les courbes avec python.

Pour afficher les resultats, il faut compiler tous les fichiers .cpp : g++ *.cpp puis exécuter avec ./a.out

Là on a les résultats qui s'affichent et les fichiers .txt créés.

Pour voir les courbes, il faut juste compiler le fichier figure.py avec la commande "python figure.py" : les courbes s'affichent dans l'ordre également pour avancer il faut fermer la courbe affichée.

Pour que l'algorithme tourne rapide , il faut diminuer nb_boucle et/ou nbsim_opt (se trouvant dans le main au début).

