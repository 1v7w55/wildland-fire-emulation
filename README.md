## Projet en C Wildland-Fire-Emulation

### Equipe 
- Serine BETTAYEB bettayebserine@gmail.com
- Sacha VANNIER svannier@et.esiea.fr
- Dimitri VERGOZ vergoz@et.esiea.fr


# Émulation d'incendie en milieu forestier
## Obligatoire:
### 1. Présentation:
- **Création d'une simulation de la propagation d'un incendie au sein d'une forêt**.
- La forêt est représentée par une matrice avec des dimensions de longueur et de largeur.
- Chaque cellule de la forêt a différentes caractéristiques : sol (**+**), arbre (__*__), feuille ( ), roche (**#**), herbe (**x**), eau (**/**), cendres (**-**), cendres éteintes (**@**).
- Une cellule a un type, un état (en feu ou non), et un degré de combustion (allant de 0 à 5).

### 2. Principales fonctionnalités attendues:
- ~~Initialiser la forêt avec des dimensions fournies par l'utilisateur~~.
- ~~Proposer un menu avec les options suivantes :~~
    - ~~Remplissage aléatoire de la forêt.~~
    - ~~Remplissage manuel de la forêt.~~ (Refaire l'affichage utilisateur pour lui demander la longueur puis la largeur et enfin de mettre sa grille.)
- Simuler un incendie avec un nombre d'itérations spécifié par l'utilisateur.
- Possibilité de revenir en arrière dans une simulation.
- Fonctionnalité pour interrompre et changer des cellules.
- Vérifier si un incendie peut se propager d'un point A à un point B.
- ~~Option pour quitter la simulation.~~

### 3. Contraintes:
- Code modulaire avec utilisation de différents fichiers `.c` et `.h`.
    - *Les fichiers .c contiennent le code source effectif du programme, tandis que*
    - *les fichiers .h définissent des interfaces, comme les déclarations de fonctions et les structures, pour assurer la modularité et la réutilisabilité du code.*
- ~~Allocation dynamique de mémoire (utilisation de malloc, etc...).~~
- ~~Utilisation de fonctions récursives (while, for).~~

### 4. Consignes et critères d'évaluation:
- Travail réalisé en trinômes.
- Présentation du projet à l'enseignante avec un rapport.
- Evaluation basée sur : 
    1. fonctionnalité, 
    2. qualité technique, 
    3. défense (présentation à l'oral), 
    4. rapport, 
    5. interface utilisateur, 
    6. améliorations éventuelles (rajout de notre part).

## Optionnel (BONUS):
1. Ajout d'un menu attrayant pour la simulation.
2. Calculer le nombre de simulations nécessaires pour brûler complètement une forêt.
3. Possibilité de sauvegarder une simulation pour y revenir plus tard.
4. Offrir à l'utilisateur la capacité de configurer la simulation (ajouter de nouveaux types de cellules ou de règles).
5. Proposer une interface utilisateur graphique en plus de l'interface en ligne de commande.
6. *Pour les utilisateurs avancés : mise en place d'une intelligence artificielle pour déterminer le meilleur point de départ d'un incendie.*

## Documentation 
- diagramme : https://lucid.app/lucidchart/22e88b6a-d144-47b1-8b71-0671290669e1/edit?viewport_loc=-732%2C-760%2C2680%2C1258%2C0_0&invitationId=inv_2c86aefa-dce3-4323-99df-44162f944eaa