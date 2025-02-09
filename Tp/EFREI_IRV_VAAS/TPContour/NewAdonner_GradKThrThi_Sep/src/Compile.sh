# Créer le répertoire bin s'il n'existe pas
mkdir -p ../bin

# Compiler EdGradientKirsh
gcc -o ../bin/EdGradientKirsh DetectionContours.c EdLibGradientKirsh4SepMasks.c EdLibThinning.c EdLibEdgeUtilities.c EdUtilities.c EdLibThreshold.c

cd ../bin

# Définir les variables d'image
nom_image="Bureau"

image="../image/${nom_image}.pgm"
imageNorm="../ImRes/${nom_image}_norm.pgm"
imagePts="../ImRes/${nom_image}_pts.pgm"

# Exécuter le programme avec les arguments appropriés
./EdGradientKirsh "$image" "$imageNorm" "$imagePts" 20