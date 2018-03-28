# Labyrinth

Le but de ce travail est de réaliser un jeu de boules qui se déplacent dans un labyrinthe.
Le jeu est constitué de 2 plateformes LPCXpresso/Mylab2 qui communiquent entre-elles par Ethernet. 
Chaque carte est commandée par un joueur qui peut faire avancer sa propre boule dans le labyrinthe, son
objectif étant de rentrer dans la cage verte en bas à droite de l’écran (voir illustration ci-dessous).
Les écrans des 2 cartes doivent donner « simultanément » la même représentation du jeu. 
Le déplacement des boules commandées utilise l’accéléromètre de chaque carte Mylab2, de sorte à
simuler le comportement d’une bille sur un plateau que l’on incline. Chaque obstacle rencontré
(murs ou autre boule) provoque un rebond de la boule.
La boule de l’adversaire et 3 autres boules « perturbatrices » sont présentes sur le plateau de jeu.
