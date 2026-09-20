# Projet de cryptographie

Application de bureau développée en Python avec **PyQt6**, permettant de
chiffrer un texte à l'aide de plusieurs méthodes classiques : **César**,
**XOR** et **Pollux**.

Ce projet a été réalisé dans un objectif pédagogique afin de découvrir
différents principes de chiffrement et de les manipuler à travers une
interface graphique.

## Fonctionnalités

-   **Chiffrement de César** : décalage des lettres vers la droite ou
    vers la gauche selon une valeur choisie.
-   **Chiffrement XOR** : combinaison du texte et d'une clé à l'aide de
    l'opérateur XOR. La clé est répétée si elle est plus courte que le
    texte.
-   **Chiffrement Pollux** : conversion du texte en code Morse, puis
    remplacement des points, tirets et séparateurs par des chiffres
    définis par une clé.
-   **Interface graphique** : saisie du texte, sélection de
    l'algorithme, configuration de la clé et affichage du résultat.

> **À noter :** ce projet est éducatif. Les méthodes implémentées sont
> des chiffrements classiques et ne doivent pas être utilisées pour
> protéger des données sensibles. L'interface actuelle permet le
> chiffrement ; les fonctions de déchiffrement présentes dans le module
> `projet.py` ne sont pas toutes accessibles depuis l'interface.

## Technologies utilisées

-   Python
-   PyQt6

## Structure du projet

``` text
.
├── interface.py   # Interface graphique PyQt6 et traitement des saisies
├── projet.py      # Fonctions de chiffrement et de déchiffrement
└── README.md      # Documentation du projet
```

## Installation

1.  Vérifier que Python 3 est installé.

2.  Cloner le dépôt GitHub ou télécharger les fichiers du projet.

3.  Installer la dépendance PyQt6 :

    ``` bash
    python -m pip install PyQt6
    ```

## Lancer l'application

Depuis le dossier du projet, exécuter :

``` bash
python interface.py
```

La fenêtre de l'application s'ouvre. Saisissez le texte, choisissez un
algorithme, renseignez la clé demandée, puis cliquez sur **Valider**.

## Utilisation des algorithmes

### César

Choisissez **César**, indiquez un décalage numérique, puis sélectionnez
le sens du décalage (**Droite** ou **Gauche**).

### XOR

Choisissez **XOR**, puis saisissez une clé textuelle. Le résultat
chiffré est affiché sous forme de valeurs numériques.

### Pollux

Choisissez **Pollux**, puis renseignez deux chiffres pour chacun des
symboles suivants : le point (`.`), le tiret (`-`) et l'espace. Ces
chiffres servent à encoder la représentation Morse du texte.

## Limites connues

-   Le traitement de César est conçu principalement pour les lettres
    majuscules A à Z.
-   Le chiffrement Pollux repose sur le code Morse défini dans le
    programme et ne prend actuellement en charge que les caractères
    présents dans cette table.
-   Les fonctions de déchiffrement ne sont pas intégrées au parcours de
    l'interface graphique.
-   Il s'agit d'un projet d'apprentissage, pas d'un outil de
    cryptographie moderne.

## Auteur

**Ayyoub Boudahba**
