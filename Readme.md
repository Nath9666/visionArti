# Rapport de Traveaux pratiques

## Introduction

Ce rapport présente les travaux pratiques réalisés dans le cadre du projet de vision artificielle. Les TP se concentrent sur deux thèmes principaux : la détection de contours et la détection de mouvement. Chaque section détaille les objectifs, la méthodologie, les résultats obtenus et les applications potentielles.

## Traveau pratique 1: Contour et détection

### Objectif

L'objectif de ce TP est de détecter les contours dans une image en utilisant des algorithmes de gradient. La détection de contours est une étape cruciale dans de nombreuses applications de vision par ordinateur, telles que la reconnaissance de formes et la segmentation d'images.

### Méthodologie

Nous avons utilisé l'algorithme de Kirsh pour calculer le gradient de l'image. Le processus comprend les étapes suivantes :

1. Prétraitement de l'image
2. Calcul du gradient
3. Seuillage
4. Affinement des contours

### Code important

#### Calcul du Gradient avec l'Algorithme de Kirsh

Le calcul du gradient est effectué à l'aide de la fonction GradientKirsh4SepMask dans le fichier DetectionContours.c. Cette fonction applique un masque de Kirsh à l'image pour détecter les contours.

#### Seuillage

Le seuillage est réalisé avec la fonction ClassicThreshold.

### Résultats

Les contours détectés sont stockés dans des fichiers d'image et peuvent être visualisés pour évaluer la précision de l'algorithme.

Pour plus de simplicité, nous avons modifié le code de compilation pour qu'il nous genere automatiquement les images de sortie.

```bash
# Créer le répertoire bin s'il n'existe pas
mkdir -p ../bin

# Compiler EdGradientKirsh
gcc -o ../bin/EdGradientKirsh DetectionContours.c EdLibGradientKirsh4SepMasks.c EdLibThinning.c EdLibEdgeUtilities.c EdUtilities.c EdLibThreshold.c


cd ../bin

# Définir les variables d'image
nom_image="PavinReal"

image="../image/${nom_image}.pgm"
imageNorm="../ImRes/${nom_image}_norm.pgm"
imagePts="../ImRes/${nom_image}_pts.pgm"

# Exécuter le programme avec les arguments appropriés
./EdGradientKirsh "$image" "$imageNorm" "$imagePts" 20
```

#### Image resultats

[Image originale](./Tp/EFREI_IRV_VAAS/TPContour/NewAdonner_GradKThrThi_Sep/Image/Bureau.pgm)

[Image normale](./Tp/EFREI_IRV_VAAS/TPContour/NewAdonner_GradKThrThi_Sep/ImRes/Bureau_norm.pgm)

[Image points](./Tp/EFREI_IRV_VAAS/TPContour/NewAdonner_GradKThrThi_Sep/ImRes/Bureau_pts.pgm)

## Traveau pratique 2: Detection de mouvement
