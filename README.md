[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/e5ZO3iBg)

# Projet Réseaux Trophiques — ING2 2024

Programme en C (console, Windows) qui permet de charger, analyser et simuler des **réseaux trophiques** (chaînes alimentaires d'un écosystème) représentés sous forme de graphe orienté : chaque sommet est une espèce, chaque arc une relation de prédation/consommation pondérée.

## Fonctionnalités

- **Chargement de réseaux** depuis des fichiers texte (Arctique, Barrière de corail, forêt pluviale de Colombie-Britannique…).
- **Export Graphviz** : génération automatique du fichier `dot/ReseauProgramme.dot` à chaque chargement.
- **Analyse du graphe** :
  - connexité (`code/connexite.c`)
  - détection de cycles (`code/maillons.c`)
  - complexité : degré moyen, densité, prédécesseurs / successeurs (`code/complexite.c`)
  - importance trophique : centralités radiale et médiane (`code/Importance_trophique.c`)
  - dépendances entre espèces (`code/algos.c`)
- **Espèces spéciales et symbiose** : détection des espèces clés et des relations de symbiose (`especes_speciales.c`, `symbiose.c`).
- **Simulation de populations** par tour, avec croissance logistique (schéma Runge-Kutta d'ordre 2), propagation le long de la chaîne alimentaire (parcours BFS) et **catastrophes naturelles ou humaines** (`code/simulation.c`).
- **Observation d'une espèce** : enregistrement de son effectif à chaque tour dans `data.txt`, puis tracé d'un graphique avec gnuplot (`graphique.gp`).

## Structure du projet

```
.
├── main.c              # Boucle principale : lecture des commandes + simulation
├── CMakeLists.txt
├── code/               # Modules (.c / .h)
│   ├── commandes.*     # Interpréteur de commandes
│   ├── programme.*     # Initialisation et tours de simulation
│   ├── graphe.*        # Structure de graphe, chargement de fichier
│   ├── algos.*         # Algorithmes sur le graphe
│   ├── simulation.*    # Dynamique des populations et catastrophes
│   ├── connexite.*  maillons.*  complexite.*  Importance_trophique.*
│   ├── especes.*  especes_speciales.*  symbiose.*
│   └── dot.*           # Export Graphviz
├── filetxt/            # Données : réseaux (dataArctique, dataBC, dataBarriereCorail) et especes.txt
├── dot/                # Fichier .dot généré
├── data.txt            # Données d'observation d'une espèce
├── graphique.gp        # Script gnuplot
└── license.txt         # Sources des données
```

### Format des fichiers de données

- `filetxt/especes.txt` : première ligne = nombre d'espèces, puis une ligne par espèce : `id nom type temps_gestation capacité_gestation valeur_nutritive besoin_nutritif domaine_vital`.
- `filetxt/data*.txt` : nombre de sommets, nombre d'arcs, puis la liste des sommets et des arcs (`source destination poids`).

## Compilation

Prérequis : un compilateur C (C11) et CMake ≥ 3.28. Le programme utilise `windows.h` (couleurs de console) : il est donc prévu pour **Windows**.

```bash
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug
```

L'exécutable `RepProj` est à lancer **depuis le dossier de build** (par exemple `cmake-build-debug/`), car les chemins des fichiers sont relatifs (`../filetxt/`, `../dot/`, `../data.txt`). Le projet s'ouvre directement dans CLion.

## Utilisation

Les commandes s'écrivent sous la forme `/commande(argument)`.

| Commande | Description |
|---|---|
| `/help` | Affiche l'aide |
| `/tuto` | Affiche le tutoriel |
| `/exit` | Quitte le programme |
| `/callgraph(fichier.txt)` | Charge un réseau depuis `filetxt/` |
| `/print` | Affiche le graphe |
| `/getespeces` | Liste les espèces présentes dans le graphe |
| `/getsommet(nomEspece)` | Se place sur le sommet d'une espèce |
| `/infoespece(espece)` | Infos notables sur l'espèce dans le réseau |
| `/modifynb(nb)` | Modifie la population de l'espèce sélectionnée |
| `/detecterespeces` | Détecte les espèces spéciales |
| `/complexite` | Affiche la complexité du graphe |
| `/sim(nb)` | Simule `nb` tours |
| `/startobs(nomEspece)` | Commence à enregistrer les effectifs d'une espèce |
| `/stopobs(nomEspece)` | Arrête l'observation et génère le graphique |

### Exemple

```
/callgraph(dataArctique.txt)
/getespeces
/startobs(Krill)
/sim(50)
/stopobs(Krill)
```

### Visualiser le graphe

```bash
dot -Tpng dot/ReseauProgramme.dot -o reseau.png
```

### Graphique d'observation

`/stopobs` exécute gnuplot avec `graphique.gp` pour produire `graphique.png` à partir de `data.txt` (gnuplot doit être installé et dans le `PATH`).

## Sources des données

Voir `license.txt`.
