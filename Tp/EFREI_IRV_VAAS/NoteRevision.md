## Espaces colorimétriques
## Extension à la couleur 
## Contours (important)
 - Kirsh 4
 - Chainage des contours
## Mouvement

## Espaces colorimétriques
 - Espaces natifs (R,V,B): c'est nos yeux les capteurs. C'est 3 bandes spectrales identiques.
    On s'en sert pour la segmentation 
    Problème : sensible aux variations d'éclérage pour la "détéction de couleur" (= "teinte")
 - Espace télévisuels (Y,u,v) (Y,Cr,Cb): Y : luminance, Cr : chrominance rouge, Cb : chrominance bleu
    On s'en sert pour la compression
 - Espace perceptif (Luminance, Teinte, Saturation) : c'est notre cerveau. "quasi" invarient aux conditions d'éclérage

 - objets colorés : 
   - Teinte "précise"
   - saturation : minimale (50, 100 à 255) ==> il faut que ça soit saturé 
   - Luminance : aucune (0 à 255)

![1736858502233](image/NoteRevision/1736858502233.png)

vert : 60 +- 15 (45 à 75)
bleu : 120 +- 15 (105 à 135)
rouge : 0 +- 15 (0 à 15 et 164 à 179)

 - objets gris : 
 - pas saturé : saturation maximale comprise entre 0 et 50 ou 100 
 - la teinte = ne veut rien dire (0,179) : on ne joue pas sur la teinte 
 - luminance

![1736859098679](image/NoteRevision/1736859098679.png)
Saturation max quand on est à 255 

![1736859339151](image/NoteRevision/1736859339151.png)

![1736859901185](image/NoteRevision/1736859901185.png)




