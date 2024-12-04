# les contours

[pdf](../Helper/pdf/SRD_S9_2023/3-SegmentationContours.pdf)

echelons noyer dans du bruit
la marche d'escalier ne peut pas exister en physique

le contour sera plus suivant une courbe de bezier a cause des différents paramètres de la caméra

## Mathématiquement

la derivée premiere est le gradient
la derivée seconde de la fonction est le laplacien

le contour est obtenu théoriquement :

- par le maximum de la norme du gradient
- par le passage à zero du laplacien

## Exemple de dection

le sens des zero nous donne le sens des contours

**bas niveau** : sortie image
**moyen niveau** : sortie numérique, primitive plus attibuts

- une liste primaires des contours
- liste des points de contours

ne plus stoker des contours mais une ligne poligonale, et donc un ensemble de segments jointifs

**haut niveau** : sortie sémantique, decisionel
Un filtre sur les attributs pour prendre la décision

## les differentes etapes

10.1 Lissage

1. Calcul du Gradient, en chaque pixel, en norme
   (amplitude du contour) et argument
2. Seuillage sur la Norme du Gradient : Contours
   Epais » et « Avec Trous »

1 et 2 c'est Canny

3. Affinage des Contours,
4. Prolongation des Contours
5. Chaînage des Contours - find COntours
6. Approximation Polygonale ou autre
   Transformation de Hough
   Directement après l'Affinage
   v/ Droites, Alignements de Droites,
   v/ Cercles, Ellipses

attention en C c'est la fonction atn2 qui donne l'argument

detection de points colorée -> HSV "invariant" à l'éclairage
Operateur sur une image -> en RVB

