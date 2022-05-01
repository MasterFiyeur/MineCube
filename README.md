![Project timelapse](assets/gif/timelapse.gif)

# Raylib project: Minecube

Ce projet scolaire vise à se familiariser avec l'environnement C++ et la bibliothèque
graphique [Raylib](https://github.com/raysan5/raylib/).

Le but est simple : créer un mini jeu en 2D ou en 3D grâce à Raylib, en utilisant quelques
fonctionnalités basiques du C++ : héritage, polymorphisme, STL, boucles, etc.

Nous avons décidé pour ce projet de reproduire le célèbre jeu Minecraft, en recréant un
petit nombre de ses caractéristiques et fonctionnalités. *Veuillez noter que les textures,
sons et musiques utilisées par notre projet proviennent directement du jeu Minecraft et sont
la propriété entière et exclusive de Mojang Studios.*


## Installation et compilation

Ce projet contient déjà la plupart des fichiers nécessaires à son utilisation : ressources
et fichiers de code sont en effet inclus dans le [dépôt GitHub](https://github.com/arcreane/raylib-kelawin),
il suffit de le télécharger.

Pour l'installation des dépendances et la compilation nous utilisons un fichier CMake, qui
vous permet très facilement de télécharger les deux dépendances (Raylib et json) puis de
compiler l'ensemble du projet. Une fois compilé vous n'aurez qu'à lancer l'exécutable.


## Caractéristiques notables

* Génération de monde procédurale via la méthode de *perlin noise*
* Distance de rendu (30 blocs) et de calculs vectoriels pour optimiser
le rendu du monde
* Shader de brouillard pour masquer la frontière de rendu (28 blocs)
* Gestion du cycle jour/nuit, avec modification de la luminosité et mouvements du soleil
* Sauvegarde et chargement automatique du monde dans un fichier JSON
* Sons et musiques d'ambiance

*Techniquement notre jeu supporte aussi les lumières ponctuelles, qu'on pourrait par
exemple utiliser pour des torches. Mais n'ayant pas pu gérer l'opacité des blocs ni
les ombres projetées, nous avons décidé de ne pas les utiliser pour le projet final.

## Contrôles en jeu

* Mouvements latéraux : WASD (ou ZQSD pour les claviers AZERTY)
* Sauter (mode sol) / monter (mode vol) : barre espace
* Descendre (mode vol) : majuscule temporaire gauche (shift)
* Sélectionner un bloc dans sa barre d'inventaire rapide : défilement de la molette
* Récupérer le bloc visé dans sa barre d'inventaire rapide : clic molette ou `P`
* Réorganiser sa barre d'inventaire rapide : `I`
* Fermer le jeu : `Esc`


## Sauvegarde du monde

Le jeu sauvegarde automatiquement votre monde lors de sa fermeture, dans le fichier
`world.json`, dans le même dossier que l'exécutable. Supprimer ce fichier vous permettra
de générer un nouveau monde et de reprendre de zéro.

Dans ce fichier est sauvegardé : la liste des blocs du monde avec leur position, la
position et l'orientation du joueur, si le joueur se trouve en mode vol, ainsi que
le temps passé en secondes depuis le début de la partie (utilisé pour les cycles jour/nuit).


# Captures d'écran

[![Quick letsplay](https://res.cloudinary.com/marcomontalbano/image/upload/v1651417297/video_to_markdown/images/streamable--ip4fu9-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://streamable.com/ip4fu9)
*Petite vidéo montrant les mécaniques principales du jeu*

![](https://i.imgur.com/4OARAxH.png)
*De nuit avec une lumière rouge : comme vous pouvez le voir, les blocs n'ont aucune opacité*

