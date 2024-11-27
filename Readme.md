# LegoTracker

Le but de ce projet est de reconnaitre le nombre de lego dans une image et de les compter.

## Installation de OpenCV

[Video de l'installation de OpenCV avec Cmake](https://youtu.be/EqoH3gspQGg)
[Installation VSCODE and OpenCV](https://youtu.be/HQJlsmIUXOQ)

## **Timeline et étapes**

### **Phase 1 : Préparation (1 semaine)**

1. **Recherche et familiarisation :**
   - Étudier les fonctionnalités d’OpenCV pour le traitement d’image.
   - Examiner des exemples de détection d’objets simples.
2. **Installation et configuration :**
   - Installer OpenCV avec un environnement de développement pour C++ (comme Visual Studio ou VS Code).
   - Configurer les dépendances nécessaires.

---

### **Phase 2 : Analyse et traitement d’image (2 semaines)**

1. **Collecte d'images :**
   - Collecter ou capturer des images de Legos dans différentes configurations.
   - Annoter les images (optionnel si un modèle d’apprentissage supervisé est nécessaire).
2. **Prétraitement d’image :**
   - Convertir les images en niveaux de gris.
   - Appliquer des filtres pour réduire le bruit (filtre gaussien, médian).
   - Binarisation (méthode d’Otsu ou adaptation locale).
3. **Segmentation des Legos :**
   - Utiliser des techniques comme la détection de contours (Canny, Sobel) pour isoler les Legos.
   - Appliquer des transformations morphologiques (dilatation, érosion) pour améliorer la segmentation.
4. **Identification des Legos :**
   - Utiliser des algorithmes comme la détection de formes géométriques ou l’analyse des composantes connectées (connected components analysis).
   - Calculer la taille et d’autres caractéristiques pour différencier les Legos.

---

### **Phase 3 : Comptage et affichage (1 semaine)**

1. **Détection et comptage :**
   - Implémenter un compteur basé sur le nombre de contours détectés.
   - Filtrer les objets par taille ou forme pour éviter les faux positifs.
2. **Affichage des résultats :**
   - Superposer des rectangles ou cercles autour des Legos détectés dans l’image d’origine.
   - Afficher le nombre total de Legos détectés.

---

### **Phase 4 : Validation et amélioration (2 semaines)**

1. **Tests avec différents scénarios :**
   - Vérifier la précision du comptage sur des images complexes (ombres, chevauchements).
   - Ajuster les paramètres du traitement d’image.
2. **Améliorations :**
   - Introduire la reconnaissance des couleurs pour distinguer les Legos par couleur.
   - Ajouter une interface utilisateur simple avec une bibliothèque comme Qt.
3. **Optimisation :**
   - Améliorer les performances pour traiter plusieurs images rapidement.

---

### **Phase 5 : Documentation et livraison (1 semaine)**

1. **Documentation :**
   - Rédiger des commentaires dans le code pour expliquer chaque étape.
   - Préparer un guide utilisateur pour exécuter le programme.
2. **Livraison :**
   - Créer un exécutable ou un installeur.
   - Fournir les fichiers nécessaires pour reproduire le projet.

---

## **Arborescence du code**

```
LegoTracker/
├── include/
│   ├── image_processing.hpp  // Fonctions pour le traitement d'image
│   ├── lego_detection.hpp    // Fonctions pour la détection de Legos
│   └── utils.hpp             // Fonctions utilitaires (chargement  d'images, affichage)
├── src/
│   ├── main.cpp              // Point d'entrée principal
│   ├── image_processing.cpp  // Implémentation des fonctions de traitement d'image
│   ├── lego_detection.cpp    // Implémentation des fonctions de détection
│   └── utils.cpp             // Implémentation des fonctions utilitaires
├── data/
│   ├── images/               // Images d'entrée
│   ├── results/              // Images avec annotations
│   └── test_cases/           // Images de test
├── tests/
│   ├── test_detection.cpp    // Tests unitaires pour la détection
│   └── test_processing.cpp   // Tests unitaires pour le traitement
├── CMakeLists.txt            // Fichier de configuration pour la compilation
└── README.md                 // Documentation du projet
```

---

## **Idées supplémentaires pour enrichir le projet**

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
