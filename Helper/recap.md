# recap des autres

Sommaire:
Espaces colorimétriques
extension à la couleur
contours:

- détection de contours

## Espaces colorimétriques

Il y a 3 espaces

- natif (RVB) nos yeux en vrai mais egalement les capteurs

C'et 3 bandes spectrales qui sont identiques

- espaces televisuel (YUV) Y luminance U et V chrominance

chrominences rouge et bleu
c'est pour la compression d'image
Y, Cr, Cb (YUV)

- espace perceptif : Luminance Teinte et Saturation (notre cerveau)

Luminance : intensité de la lumière
Teinte : couleur
Saturation : pureté de la couleur

Quasi invarient aux condition d'éclairage

Object colorée

- teinte precise
- saturation faible
- luminance aucune

Cercle des couleurs:

- 3 couleurs primaires
  rouge, bleu et vert
- 3 couleurs primaires opoosées
  cyan, magenta et jaune

Codage physique:
[0 - 359] sur un cercle
Codage informatique:
[0 - 255] sur un cercle

## detection de contours

image 16 * 16


|     |     |     |     |     |     |     |     |     | X1  |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
|     |     |     |     |     |     |     |     |     |     | X2  |     |     |     |     |     |
|     |     |     | X3  | X4  | x5  | X6  |     |     |     |     | X7  |     |     |     |     |
|     |     | X8  |     |     |     |     | X9  |     |     |     |     | X10 |     |     |     |
|     | X11 |     |     |     |     |     | X12 |     |     |     |     | X13 |     |     |     |
|     | X14 |     |     |     |     |     | X15 |     |     |     |     | X16 |     |     |     |
|     |     | X17 |     |     |     |     | X18 |     |     |     |     |     | X19 | X20 |     |
|     |     |     | X21 |     | X22 | X23 |     | X24 |     |     |     |     |     | X25 |     |
|     |     |     |     | X26 |     |     |     |     | X27 |     |     |     |     | X28 | X29 |
|     |     |     |     |     |     |     |     |     |     | X30 |     |     |     |     |     |
|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
|     |     |     |     |     |     |     |     |     |     | X31 | X32 | X33 | X34 | X35 | X36 |
|     |     |     |     |     |     | X37 | X38 | X39 | X40 |     |     |     |     |     |     |
|     |     |     | X41 | X42 | X43 |     |     |     |     |     |     |     |     |     |     |
| X44 | X45 | X46 |     |     |     |     |     |     |     |     |     |     |     |     |     |
|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
