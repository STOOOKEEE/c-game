# Audit TD15-TD16 - Soutenance Partie 1

Source auditee : `Projet.pdf`, section `9.2 TD15-TD16 : Soutenance - Partie 1`.

## Verdict

Le projet couvre les attentes de la grille Partie 1. Les deux ecarts identifies avant
correction ont ete traites :

- UML final regenere : `UML.svg` est la source maintenable, `UML.png` est l'image a presenter.
- Encapsulation renforcee : les attributs de `Entity`, `Monster`, `ActAction` et
  `BestiaryEntry` sont prives et exposes via methodes.

## Checklist de notation

| Critere | Statut | Preuves dans le code |
| --- | --- | --- |
| UML final clair et a jour | OK | `UML.svg`, `UML.png` |
| Heritage | OK | `Player : Entity`, `Monster : Entity`, categories derivees dans `Monster.h` |
| Classe abstraite | OK | `Entity::displayStats() = 0`, `Monster::getMaxActs() = 0`, `Monster::clone() = 0` |
| Classes derivees | OK | `NormalMonster`, `MiniBossMonster`, `BossMonster` |
| Encapsulation | OK | Attributs prives + getters/setters dans les classes principales |
| Polymorphisme | OK | `getMaxActs()` retourne 2/3/4 selon la categorie |
| Systeme ACT et Mercy | OK | Catalogue dans `ActAction.h`, effets positifs/negatifs, bornage dans `Monster::modifyMercy()` |
| Lecture de fichiers | OK | `FileLoader::loadItems()`, `FileLoader::loadMonsters()`, messages fichier introuvable et lignes invalides numeriques |
| Menu principal | OK | Bestiaire, combat, stats, items, quitter dans `Game::mainMenu()` |
| Combat | OK | `FIGHT`, `ACT`, `ITEM`, `MERCY`, puis tour monstre dans `Combat.cpp` |
| Fin a 10 victoires | OK | `Game::mainMenu()` appelle `UI::showEnding()` a 10 victoires |
| Fins multiples | OK | Genocide, pacifist, neutral dans `UI::showEnding()` |

## Points a expliquer pendant la soutenance

- `Entity` porte les statistiques communes et force `displayStats()` par methode virtuelle pure.
- `Monster` ajoute la categorie, la Mercy et les actions ACT, puis chaque sous-classe
  specialise `getMaxActs()`.
- Les monstres charges depuis `monsters.csv` sont des templates clones avant chaque combat.
- `ActAction` garde les textes et les impacts Mercy dans le code, tandis que `monsters.csv`
  ne contient que les identifiants d'actions.
- `BestiaryEntry` garde un historique simple des combats gagnes pour le menu bestiaire.

## Risques non bloquants

- La gestion memoire utilise `new`/`delete`. C'est coherent avec le niveau du projet,
  mais il faut pouvoir expliquer que `Game::~Game()` libere les templates et que les
  monstres clones sont supprimes apres combat.
- Il n'y a pas de framework de tests complet. Le check ajoute dans `tests/check_encapsulation.sh`
  couvre l'encapsulation, et la compilation avec warnings sert de verification de base.
