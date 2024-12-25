
# Définir les chemins pour OpenCV
OPENCV_INCLUDE_DIR="./opencv/build/include/"
OPENCV_LIB_DIR="./opencv/build/x64/vc16/lib/"

# Compiler le fichier main.cpp avec les chemins d'inclusion et de bibliothèque pour OpenCV
g++ ./LegoTracker/tests/main.cpp -o ./bin/main_test -I${OPENCV_INCLUDE_DIR} -L${OPENCV_LIB_DIR} -lopencv_core310 -lopencv_highgui310 -lopencv_imgproc310

# Vérifier si la compilation a réussi
if [ $? -eq 0 ]; then
    # Exécuter le fichier compilé
    ./bin/main_test
else
    echo "Erreur: La compilation a échoué."
fi