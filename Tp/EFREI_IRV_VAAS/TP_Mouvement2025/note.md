## Note sur le TP

Sur linux, si le compile.sh n'est pas executable : 

Pour que le compile.sh soit executable  : chmod +x compile.sh

pour le compiler : ./compile.sh


Bruit de détection : 
- FAUX POSITIF, c'est a dire qu'il y a des pixels qui sont détéctés comme étant en mouvement alors qu'il ne le sont pas
- FAUX NEGATIF, c'est a dire qu'il y a des pixels qui sont en mouvement mais qui ne sont pas détéctés comme tel 

"Statiques" :
    - Ouverture = érosion + dilatation : enlève les bruits faux positifs (petites formes)
    - Fermeture = dilatation + érosion : enlève les bruits faux négatifs (petites trous = petite formes du fond)
"Dynamiques": On considère le pixel en mouvement si on le détecte positif un minimum de fois.