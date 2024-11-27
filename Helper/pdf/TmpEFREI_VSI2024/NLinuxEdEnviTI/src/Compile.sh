# Compilation des Fichiers
gcc -o ../bin/EdSimpleScan EdSimpleScan.c EdLibSimpleScan.c EdUtilities.c
echo "Compilation EdSimpleScan terminee"

gcc -o ../bin/EdScanVois3 EdScanVois3.c EdLibScanVois3.c EdUtilities.c
echo "Compilation EdScanVois3 terminee" 

gcc -o ../bin/EdMeanFiltering EdMeanFiltering.c EdLibMeanFiltering.c EdUtilities.c
echo "Compilation EdMeanFiltring terminee" 

gcc -o ../bin/EdGaussFiltering EdGaussFiltering.c EdLibGaussFiltering.c EdUtilities.c
echo "Compilation EdGaussFiltring terminee" 

gcc -o ../bin/EdMedianFiltering EdMedianFiltering.c EdLibMedianFiltering.c EdUtilities.c
echo "Compilation EdMedianFiltring terminee"

gcc -o ../bin/EdHatThresholdEros EdHatThresholdEros.c EdLibHatThreshold.c EdLibMorphoMath.c EdUtilities.c
echo "Compilation EdHatThreshold terminee"
