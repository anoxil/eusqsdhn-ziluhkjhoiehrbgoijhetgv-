

# Analyse et traitement d’images dans le cadre de la RoboCup



Dans le cadre du projet vision de l'option robotique (promo 2019/2020) de l'ENSEIRB-MATMECA, nous avons était amené à travailler sur de la detection d'objets sur des vidéos enregistrées par l'équipe Rhoban dans le cadre de la robocup.

### Lot 1 : Terrain

Notre équipe composé de Raphaël **Brès**, Alban **Chauvel**, et Aurélien **Roffet** s'est focalisée sur la détection de terrain (*Playfield*). Les consignes sont les suivants :

- Détecter le terrain et créer un masque du terrain.

- Attentes : 
  - Pas de faux négatifs (ne pas masquer le terrain). 
  - Faux positifs un peu toléré (dépassement en bordure du terrain).



### Pré-requis

Pour compiler le programme vous devez posseder OpenCV 2.4 .

Le programme fonctionne avec un fichier vidéo. Pour génerer un fichier vidéo à partir des images fournit par les données du projet, téléchargez les images à cette adresse, décompressez le dossier, et tapez la commande suivante pour log1, log2 ou log3 :

```bash
ffmpeg -framerate 10 -i %03d-rgb.png -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p output.mp4
```

Pour le cas particulier de log4, tapez la commande suivante :

```bash
ffmpeg -framerate 10 -i %02d-rgb.png -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p output.mp4
```



### Installation

Pour compiler et pouvoir utiliser le code, téléchargez le dépot git, et tapez les commandes :

```bash
cd src/
make
```

Pour lancer le dernier programme de détection de terrain, placez vous dans le dossier src et tapez :

```bash
./threshold-medianfilter-video-interests <fichier.mp4>
```



### Arborescence des fichiers

Parmis les fichiers présent dans ce dépôt :

* <u>*threshold-opening.cpp :*</u>
  ffffff
* <u>*threshold-medianfilter.cpp :*</u>
  ffffff
* <u>*threshold-medianfilter-video.cpp :*</u>
  ffffff
* <u>*threshold-medianfilter-video-interests.cpp :*</u>
  ffffff
* <u>*morphology.cpp/hpp :*</u>
  ffffff
* <u>*compare.cpp/h :*</u>
  ffffff