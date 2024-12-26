# LegoTracker

Le but de ce projet est de reconnaître le nombre de Lego dans une image et de les compter.

## Installation de OpenCV

Dans un premier temps, il est nécessaire d'installer OpenCV sur votre machine. 
Pour cela je vous conseille de suivre se tuto : [Installation OpenCV](https://youtu.be/aMXQshF7zdo)
Ou d'aller sur le site officiel d'OpenCV : [OpenCV](https://opencv.org/releases/)

Vous avez donc un .exe nommé "opencv-4.6.0-vc14_vc15.exe" que vous allez installer sur votre machine. 
Une fois cliquer sur le .exe, vous allez avoir une fenêtre qui va s'ouvrir.
Et vous aller mettre openCV dans le dossier VisionArti.

Vous aurrez juste a aller a l'adresse suivante pour configurer vos varible d'environnement:
[.env](./opencvbuild/setup_vars_opencv4.cmd)

Une fois cela fait je vous conseille de fermer puis réouvrir VSCode pour que les changements soit pris en compte.
Après cela vous pouvvez lancer le programme.


## **Utilisation de modèles d'intelligence artificielle**

Le projet intègre également des modèles d'intelligence artificielle pour améliorer la reconnaissance des pièces de Lego. Voici quelques idées :

1. **Reconnaissance des couleurs :**
   - Utiliser la décomposition HSV pour détecter les couleurs principales des Legos.
   - Compter les Legos par couleur (par exemple, 5 rouges, 3 bleus).

2. **Détection avancée avec apprentissage automatique :**
   - Entraîner un modèle léger comme un réseau convolutif pour détecter les Legos.
   - Utiliser des modèles pré-entraînés comme YOLO ou SSD si nécessaire.

3. **Reconnaissance de formes :**
   - Distinguer les types de Legos (par exemple, 2x2, 2x4) en fonction de leur taille ou de leur aspect.

4. **Vidéo en temps réel :**
   - Adapter le programme pour détecter et compter les Legos dans une vidéo ou via une webcam.

5. **Statistiques avancées :**
   - Afficher des graphiques ou des tableaux avec des données comme les tailles et les couleurs.

---

## **Arborescence du code**

```
├── include/
│   ├── image_processing.hpp  // Fonctions pour le traitement d'image
│   ├── lego_detection.hpp    // Fonctions pour la détection de Legos
│   └── utils.hpp             // Fonctions utilitaires (chargement d'images, affichage)
├── src/
│   ├── main.cpp              // Point d'entrée principal
│   ├── image_processing.cpp  // Implémentation des fonctions de traitement d'image
│   ├── lego_detection.cpp    // Implémentation des fonctions de détection
│   └── utils.cpp             // Implémentation des fonctions utilitaires
├── data/
│   ├── images/               // Images d'entrée
│   └── results/              // Donnée (.xlm ou .json) de sortie
├── models/
│   ├── trained_model.h5      // Modèle d'apprentissage automatique pré-entraîné
│   └── model_training.py      // Code pour entraîner un modèle d'apprentissage automatique
├── CMakeLists.txt            // Fichier de configuration pour la compilation
└── README.md                 // Documentation du projet
```

---

## Projet soutenance le 15/01/2025 avec un rapport à rendre.

# Amelioration possible du projet par le cour

Approximation Polygonale ou autre
Transformation de Hough
Directement après l'Affinage
Segmentation de region
Algorithme d’Horowicz et Pavlidis