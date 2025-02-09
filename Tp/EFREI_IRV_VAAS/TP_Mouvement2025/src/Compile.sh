mkdir -p ../bin

gcc -o ../bin/EdMotionDetect EdMotionDetect.c EdLibMotionDetect.c EdUtilities.c
echo "EdMotionDetect compiled"

gcc -o ../bin/EdMotionDetectFond EdMotionDetectFond.c EdLibMotionDetectFond.c EdUtilities.c
echo "EdMotionDetectFond compiled"

mkdir -p ../ImRes
echo "ImRes directory created"

cd ../bin

./EdMotionDetect.exe NImCote0000.ppm 30

# deplacer tout les fichiers dans ImRes dans le dossier NImCote

cd ../ImRes


./EdMotionDetectFond.exe NImCote0000.ppm 30 0.01


