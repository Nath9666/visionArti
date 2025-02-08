# Créer le répertoire bin s'il n'existe pas
mkdir -p ../bin

# Compiler EdMotionDetect
gcc -o ../bin/EdMotionDetect EdMotionDetect.c EdLibMotionDetect.c EdUtilities.c
echo "EdMotionDetect compiled"

# Compiler EdGabMotionDetect
gcc -o ../bin/EdGabMotionDetect EdGabMotionDetect.c EdLibGabMotionDetect.c EdUtilities.c
echo "EdGabMotionDetect compiled"