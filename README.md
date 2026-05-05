# Brawl Tale - RPG Console en C++

Un jeu RPG au tour par tour en console, inspire d'Undertale et de Brawl Stars. Le joueur affronte des monstres avec le choix de les combattre ou de les epargner via un systeme de mercy.

## Compilation et execution

```bash
g++ -std=c++17 -o game main.cpp Game.cpp Player.cpp Monster.cpp Entity.cpp Item.cpp Combat.cpp UI.cpp FileLoader.cpp
./game
```

## Architecture du projet

```
.
├── main.cpp            # Point d'entree
├── Game.h/.cpp         # Boucle principale, menu, gestion des combats
├── Entity.h/.cpp       # Classe abstraite de base (nom, hp, atk, def)
├── Player.h/.cpp       # Joueur (inventaire, kills, spares, victories)
├── Monster.h/.cpp      # Monstres (Normal, MiniBoss, Boss) + polymorphisme
├── Combat.h/.cpp       # Logique de combat tour par tour
├── Item.h/.cpp         # Objets (potions, snacks)
├── FileLoader.h/.cpp   # Chargement des donnees depuis les fichiers CSV
├── UI.h/.cpp           # Affichage (bestiaire, stats, inventaire, fin de jeu)
├── ActAction.h         # Actions ACT (joke, compliment, pet...) + catalogue
├── BestiaryEntry.h     # Structure pour le bestiaire
├── items.csv           # Donnees des objets
└── monsters.csv        # Donnees des monstres
```

## Concepts C++ utilises

### Heritage et polymorphisme

`Entity` est une classe abstraite avec une methode virtuelle pure `displayStats()`. `Player` et `Monster` en heritent. `Monster` est elle-meme abstraite avec `getMaxActs()` et `clone()`, et possede 3 sous-classes :

- `NormalMonster` - 2 actions ACT max
- `MiniBossMonster` - 3 actions ACT max
- `BossMonster` - 4 actions ACT max

### Chargement de fichiers (FileLoader)

Les donnees du jeu sont externalisees dans des fichiers CSV pour pouvoir les modifier sans recompiler.

**Parsing CSV** - Chaque ligne est lue puis decoupee avec `std::getline(stream, variable, ';')` :

```cpp
// Lit jusqu'au prochain ';' et stocke dans la variable
// Retourne false si la lecture echoue -> on saute la ligne
if (!std::getline(ss, catStr, ';')) continue;
if (!std::getline(ss, name, ';'))   continue;
if (!std::getline(ss, hpStr, ';'))  continue;
```

C'est l'equivalent d'un `split(";")` en C++. Le 3e argument de `std::getline` change le delimiteur de `\n` a `;`.

**Format de monsters.csv** :

```
CATEGORIE;Nom;HP;ATK;DEF;MercyGoal;Act1;Act2;Act3;Act4
NORMAL;Shelly;30;7;2;100;COMPLIMENT;DANCE;-;-
BOSS;Spike;80;15;5;100;PET;COMFORT;JOKE;OFFER_SNACK
```

**Format de items.csv** :

```
Nom;Type;Valeur;Quantite
Potion;HEAL;15;3
```

### Systeme de mercy

Chaque monstre a une jauge de mercy (0 a `mercyGoal`). Les actions ACT modifient cette jauge :

| Action       | Impact mercy | Description                        |
|--------------|-------------:|------------------------------------|
| OFFER_SNACK  |          +30 | Partager un energy drink           |
| COMFORT      |          +25 | Donner un calin                    |
| COMPLIMENT   |          +20 | Dire qu'ils sont les meilleurs     |
| PET          |          +20 | Tapoter la tete                    |
| REASON       |          +20 | Proposer de faire equipe           |
| JOKE         |          +15 | Raconter une blague                |
| DANCE        |          +15 | Faire la default dance             |
| OBSERVE      |          +10 | Etudier leurs mouvements           |
| STARE        |          -10 | Les fixer du regard                |
| INSULT       |          -15 | Les traiter de noob                |

Quand la mercy atteint le `mercyGoal`, le joueur peut epargner le monstre au lieu de le tuer.

### Autres concepts

- **Encapsulation** - Attributs prives, accesseurs/modificateurs publics
- **Classe abstraite** - `Entity` avec methode virtuelle pure
- **Clonage** - Pattern `clone()` pour copier les monstres templates avant combat
- **Gestion memoire** - `new`/`delete` pour les monstres, destructeur dans `Game`
- **Aleatoire** - `std::mt19937` pour les degats de combat
- **Fichiers** - `std::ifstream` + `std::stringstream` pour le parsing CSV
