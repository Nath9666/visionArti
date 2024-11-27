# Compilation des Fichiers
gcc -o EdSimpleScan EdSimpleScan.c EdLibSimpleScan.c EdUtilities.c
mv EdSimpleScan ../bin/
echo "Compilation EdSimpleScan terminee"

gcc -o EdScanVois3 EdScanVois3.c EdLibScanVois3.c EdUtilities.c
mv EdScanVois3 ../bin/
echo "Compilation EdScanVois3 terminee" 
