# Plan de Présentation PowerPoint : LegoTracker

## Diapositive 1 : Titre

- **Titre :** LegoTracker
- **Sous-titre :** Reconnaissance et comptage de Legos dans une image
- **Auteurs :** Nathan MOREL, Alexandre BÉRAUD, Tom BEAUPUIS
- **Date :** 15/01/2025

## Diapositive 2 : Introduction

- **Objectif du projet :** Reconnaître et compter le nombre de pièces de Lego dans une image.
- **Contexte et motivation :** Importance de l'automatisation dans la reconnaissance d'objets.

## Diapositive 3 : Méthodologie

- **Étapes principales :**
  - Prétraitement de l'image
  - Segmentation de région
  - Détection des contours
  - Identification des Legos
- **Image :** Schéma de flux de traitement d'image

## Diapositive 4 : Prétraitement de l'image

- **Étapes :**
  - Conversion en niveaux de gris
  - Filtrage gaussien
  - Binarisation
- **Code :**

  ```cpp
  Mat processImage(const Mat& inputImage) {
      Mat grayImage = convertToGray(inputImage);
      Mat blurredImage = applyGaussianBlur(grayImage, 5);
      Mat binaryImage = binarizeImage(blurredImage);
      return binaryImage;
  }
  ```

- Image : Exemple d'image avant et après chaque étape de prétraitement

## Diapositive 5 : Segmentation de région

- Méthode : Croissance de région

```cpp
int detectLegos(const cv::Mat& inputImage, std::vector<cv::Rect>& detectedLegos, int seuil, int thresh, bool ImageDisplay) {
    cv::Mat labels, stats, centroids;
    int numLabels = cv::connectedComponentsWithStats(binaryImage, labels, stats, centroids, 8, CV_32S);
    // Identification des Legos par leurs régions
}
```

- Image : Exemple visuel de segmentation

## Diapositive 6 : Détection des contours

- Algorithme : Détection de contours de Canny

```cpp
cv::Canny(binaryImage, cannyOutput, thresh, thresh * 2);
std::vector<std::vector<cv::Point>> contours;
cv::findContours(cannyOutput, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
```

Image : Exemple visuel de détection des contours

## Diapositive 7 : Identification des Legos

- Étapes :
  Filtrage des petites régions
  Approximation polygonale des contours
- Code :

```cpp
for (size_t i = 0; i < approxContours.size(); i++) {
    double area = cv::contourArea(approxContours[i]);
    if (area > seuil) {
        legoCount++;
        cv::Rect boundingBox = cv::boundingRect(approxContours[i]);
        detectedLegos.push_back(boundingBox);
    }
}
```

- Image : Exemple visuel d'identification des Legos

## Diapositive 8 : Résultats

Nombre de Legos détectés : Affichage des résultats
Comparaison avec les données JSON :

```cpp
float similarity = compareImageToJson(detectedLegos, "./data/results/1001.json");
```

## Diapositive 9 : Conclusion

Résumé des résultats obtenus : Précision du système

Limites et défis rencontrés : Ajustement des paramètres, détection des petits objets

## Diapositive 10 : Perspectives

**Améliorations futures :**
Utilisation de modèles d'apprentissage automatique
Détection en temps réel via une webcam
Amélioration de la précision
**Image** : Schéma de modèle d'apprentissage automatique

## Diapositive 11 : Annexes

Liens vers les ressources et datasets utilisés :

- DataSet LegoBricks OnebyOne
- DataSet LegoBricks OnebyOne 3D
- DataSet LegoBricks OnebyOne reel
- DataSet LegoBricks Vrack reel

## Diapositive 12 : Questions et Réponses

Ouverture pour les questions du public

## Diapositive 13 : Remerciements

Remerciements aux contributeurs et aux sources d'inspiration
