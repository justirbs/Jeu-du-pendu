# TD – Pendu

## Arborescence du projet :
- Dans /bin se trouvent les fichiers objets servant à la compilation
- Dans /doc se trouve la documentation Doxygen
- Dans /src se trouvent tous les fichiers .c et .h contenant le code source
- Dans /files se trouve le fichier mots.txt contenant les mots à deviner

## Compilation :
  Pour compiler le programme il faut exécuter la commande suivante à la racine du projet :
  ```
  make
  ```

## Exécution :
  Pour exécuter le programme il faut exécuter la commande suivante à la racine du projet avec en argument la méthode à utiliser : 
  ```
  ./TP10
  ```

## Documentation :
  Pour générer la documentation Doxygen il faut exécuter la commande suivante à la racine du projet :
  ```
  make doc
  ```
  La documentation sera ainsi générée dans le dossier /doc et est accessible à partir du fichier /doc/html/index.html par exemple

## Nettoyage du projet :
  Pour effacer la documentation générée, les fichiers objets et la dernière sauvegarde il faut exécuter la commande suivante à la racine du projet :
  ```
  make clean
  ```
