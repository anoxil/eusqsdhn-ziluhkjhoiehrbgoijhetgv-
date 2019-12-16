

# Analyse et traitement d’images dans le cadre de la RoboCup



Dans le cadre du projet vision de l'option robotique (promo 2019/2020) de l'ENSEIRB-MATMECA, nous avons était amené à travailler sur de la détection d'objets sur des vidéos enregistrées par l'équipe Rhoban dans le cadre de la robocup.

### Lot 1 : Terrain

Notre équipe composée de Raphaël **Brès**, Alban **Chauvel**, et Aurélien **Roffet** s'est focalisée sur la détection de terrain (*Playfield*). Les consignes sont les suivants :

- Détecter le terrain et créer un masque du terrain.

- Attentes : 
  - Pas de faux négatifs (ne pas masquer le terrain). 
  - Faux positifs un peu tolérés (dépassement en bordure du terrain).



### Prérequis

Pour compiler le programme, vous devez posséder OpenCV 2.4 .

Le programme fonctionne avec un fichier vidéo. Pour générer un fichier vidéo à partir des images fournit par les données du projet, téléchargez les images à cette adresse, décompressez le dossier, et tapez la commande suivante pour log1, log2 ou log3 :

```bash
ffmpeg -framerate 10 -i %03d-rgb.png -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p output.mp4
```

Pour le cas particulier de log4, tapez la commande suivante :

```bash
ffmpeg -framerate 10 -i %02d-rgb.png -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p output.mp4
```



### Installation

Pour compiler et pouvoir utiliser le code, téléchargez le dépôt git, et tapez les commandes :

```bash
cd src/
make
```

Pour lancer le dernier programme de détection de terrain, placez vous dans le dossier src et tapez :

```bash
./threshold-medianfilter-video-interests <fichier.mp4>
```



### Arborescence des fichiers

Parmi les fichiers présents dans ce dépôt :

* <u>*threshold-opening.cpp :*</u>
  L'un des tout premiers tests, en utilisant l'érosion et la dilatation, temps de calcul trop long pour un fichier live.
* <u>*threshold-medianfilter.cpp :*</u>
  Début d'utilisation de la détection de contours sur les images pures.
* <u>*threshold-medianfilter-video.cpp :*</u>
  Détection du contour du terrain à partir d'un fichier vidéo. 
* <u>*threshold-medianfilter-video-interests.cpp :*</u>
  Détection du contour du terrain avec renforcement par points d'intérêts.
* <u>*morphology.cpp/hpp :*</u>
  Librairie utilisée pour *threshold-opening*.cpp.
* <u>*compare.cpp/h :*</u>
  Programme utilisé pour calculer les pourcentages de faux positif/négatif à partir de résultats attendus. 