# **Introduction :**

GomokuGame est un projet visant à développer une intelligence artificielle (IA) 
capable de jouer au jeu de stratégie Gomoku Ce jeu à deux joueurs nécessite des 
algorithmes avancés pour déterminer les coups optimaux. Nous avons utilisé les algorithmes 
Minimax et Alpha-Beta,et le projet inclut une interface graphique développée en C avec 
la bibliothèque SDL.  

##  Algorithmes Utilisées
- Algorithme Minimax et Alpha-Beta Pruning.
- Tester le jeu avec l'algorithme Minimax via le lien :
  https://github.com/MrsMeriem/GomokuGame_MinMax.git
  
## Technologies Utilisées  
- Langages de Programmation : C   
- Bibliothèque Graphique : SDL   
- IDE : Visual Studio   
- WSL

## Membres:  
- EL AITA Meriem   
- BABA Salma   
- DESAUBLIAUX Arthur  
## Groupe:    
3A FISA POLYTECH Marseille  
2023-2024   
   
## Exécution  
Vérifier l'installation de SDL2   
sudo apt-get update   
sudo apt-get install libsdl2-dev   
sudo apt-get install libsdl2-image-dev   
sudo apt-get install libsdl2-ttf-dev   


## Pour exécuter le projet :   
1. Supprimez tout dans le dossier build ou supprimez le dossier et recréez-le.   
2. Accédez au dossier build :   
cd build   
3. Construisez le projet   
cmake ..   
4. Exécutez le projet :   
make run    

### Instructions supplémentaires pour CMake :   
Utilisation de CMakeLists.txt :   
Le fichier CMakeLists.txt est utilisé pour configurer le projet. Il génère automatiquement un Makefile,
qui est utilisé pour compiler et lier le projet.   
Le dossier cmake contient des scripts nécessaires pour que CMakeLists.txt puisse localiser les bibliothèques 
SDL et leurs dépendances. Cela permet à CMake de configurer correctement le projet en trouvant les bibliothèques 
requises et en définissant les chemins d'inclusion et de liaison.   
Les scripts CMake (comme FindSDL2.cmake) aident à localiser ces en-têtes et bibliothèques sur le système de fichiers,
quel que soit le système d'exploitation ou l'emplacement d'installation.   

## À propos du jeu   
- Si le jeu est trop lent, changez MAX_DEPTH pour ajuster la profondeur maximale de l'algorithme de recherche définie par défaut à 3 dans MinMax.h
- Pour changer le nombre de pièces alignées nécessaires pour gagner, modifiez la constante MAX_WIN, définie par défaut à 5 dans board.h
