# ALTERDUNE

`ALTERDUNE` est un mini-jeu RPG en console réalisé en C++. Le projet met en pratique les notions principales de programmation orientée objet à travers un jeu au tour par tour : joueur, monstres, objets, actions ACT, combats, bestiaire et fins multiples.

Le joueur affronte des monstres tirés aléatoirement. Il peut les combattre avec `FIGHT` ou tenter de les épargner avec le système `ACT` / `MERCY`.

## Objectifs du projet

D'après le sujet `Projet.pdf`, le projet doit permettre de travailler :

- l'encapsulation : attributs privés, accesseurs et modificateurs ;
- l'héritage : joueur, monstres et catégories de monstres ;
- le polymorphisme : comportement différent selon la catégorie du monstre ;
- la composition : inventaire, actions ACT, bestiaire ;
- la lecture de fichiers CSV pour initialiser les objets du jeu.

## Compilation et exécution

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -o game main.cpp Game.cpp Player.cpp Monster.cpp Entity.cpp Item.cpp Combat.cpp UI.cpp FileLoader.cpp
./game
```

## Démarrage d'une partie

Au lancement du programme :

1. Le joueur saisit le nom de son personnage.
2. Le jeu charge `items.csv`, qui contient l'inventaire initial.
3. Le jeu charge `monsters.csv`, qui contient les ennemis possibles.
4. Le jeu affiche un résumé avec le nom du joueur, ses HP et ses objets.

Si un fichier obligatoire est introuvable, le jeu affiche un message d'erreur et s'arrête proprement.

## Menu principal

Le menu principal contient les fonctionnalités demandées dans le sujet :

- bestiaire ;
- démarrer un combat ;
- statistiques du personnage ;
- items ;
- quitter.

Le bestiaire affiche les monstres vaincus avec leur nom, leur catégorie, leurs statistiques principales et le résultat du combat : tué ou épargné.

## Combat

Un combat oppose le joueur à un monstre. Tant que les deux sont vivants, le joueur choisit une action, puis le monstre attaque si le combat n'est pas terminé.

Les actions disponibles sont :

- `FIGHT` : attaque directe du monstre ;
- `ACT` : interaction avec le monstre pour modifier sa Mercy ;
- `ITEM` : utilisation d'un objet de soin ;
- `MERCY` : épargne du monstre si sa Mercy est suffisante.

Les dégâts sont calculés avec un tirage aléatoire entre `0` et les HP maximum du défenseur. Si le résultat vaut `0`, l'attaque est ratée. Les HP ne peuvent pas descendre sous `0`.

## Système ACT et Mercy

Chaque monstre possède une jauge de Mercy. Les actions ACT modifient cette jauge :

- impact positif : le monstre s'apaise ;
- impact négatif : le monstre s'énerve ;
- la Mercy est toujours bornée entre `0` et son objectif.

Quand la Mercy atteint l'objectif du monstre, le joueur peut utiliser `MERCY` pour gagner le combat sans tuer le monstre.

Les actions ACT sont prédéfinies dans le code C++ dans un catalogue. Le fichier `monsters.csv` ne stocke que les identifiants des actions disponibles pour chaque monstre.

## Catégories de monstres

Chaque monstre appartient à une catégorie qui détermine le nombre d'actions ACT disponibles :

| Catégorie | Nombre d'actions ACT |
| --- | ---: |
| `NORMAL` | 2 |
| `MINIBOSS` | 3 |
| `BOSS` | 4 |

Cette différence est implémentée par polymorphisme avec la méthode `getMaxActs()`.

## Conditions de fin

La partie se termine lorsque le joueur atteint 10 victoires.

Trois fins sont possibles :

- fin génocidaire : tous les monstres vaincus ont été tués ;
- fin pacifiste : tous les monstres vaincus ont été épargnés ;
- fin neutre : le joueur a à la fois tué et épargné des monstres.

## Fichiers de données

### `items.csv`

Format :

```text
nom;type;valeur;quantite
```

Exemple :

```text
Potion;HEAL;15;3
Snack;HEAL;8;5
SuperPotion;HEAL;30;1
```

Dans ce projet, le type principal est `HEAL`, qui soigne le joueur.

### `monsters.csv`

Format :

```text
categorie;nom;hp;atk;def;mercyGoal;act1;act2;act3;act4
```

Règles :

- `NORMAL` utilise `act1` et `act2` ;
- `MINIBOSS` utilise `act1`, `act2` et `act3` ;
- `BOSS` utilise les quatre actions ;
- les identifiants ACT doivent exister dans le catalogue du code.

## Architecture du projet

```text
.
├── main.cpp            # Point d'entrée
├── Game.h/.cpp         # Lancement du jeu, menu principal, combats
├── Entity.h/.cpp       # Classe abstraite commune : nom, HP, ATK, DEF
├── Player.h/.cpp       # Joueur : inventaire, kills, spares, victoires
├── Monster.h/.cpp      # Monstres et catégories : Normal, MiniBoss, Boss
├── Combat.h/.cpp       # Logique de combat au tour par tour
├── Item.h/.cpp         # Objets utilisables par le joueur
├── FileLoader.h/.cpp   # Chargement de items.csv et monsters.csv
├── UI.h/.cpp           # Affichages : menu, bestiaire, stats, fins
├── ActAction.h         # Catalogue des actions ACT
├── BestiaryEntry.h     # Entrées du bestiaire
├── items.csv           # Inventaire initial
└── monsters.csv        # Monstres disponibles
```

## Notions C++ utilisées

- `Entity` est une classe abstraite grâce à `displayStats() = 0`.
- `Player` et `Monster` héritent de `Entity`.
- `NormalMonster`, `MiniBossMonster` et `BossMonster` héritent de `Monster`.
- `getMaxActs()` illustre le polymorphisme : 2, 3 ou 4 actions selon le type réel du monstre.
- Les attributs principaux sont privés et exposés avec des accesseurs/modificateurs.
- Les données sont chargées avec `std::ifstream`, `std::stringstream` et `std::getline`.
- L'aléatoire est géré avec `<random>` et `std::mt19937`.

## Évaluation TD15-TD16

La soutenance Partie 1 doit présenter :

- le diagramme UML final ;
- toutes les fonctionnalités implémentées ;
- une démonstration du jeu.

Les critères principaux sont :

- UML final clair et à jour ;
- héritage, classe abstraite et classes dérivées ;
- encapsulation ;
- polymorphisme ;
- système ACT et Mercy ;
- lecture de `items.csv` et `monsters.csv` ;
- menu principal complet ;
- système de combat complet ;
- condition de fin à 10 victoires et fins multiples.
