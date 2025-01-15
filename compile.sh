# Chemins vers les répertoires d'OpenCV et RapidJSON
OPENCV_INCLUDE_DIR="C:/Users/Nathan/Documents/Projet/visionArti/opencv/build/include"
OPENCV_LIB_DIR="C:/Users/Nathan/Documents/Projet/visionArti/opencv/build/x64/vc14/lib"
RAPIDJSON_INCLUDE_DIR="C:/Users/Nathan/Documents/Projet/visionArti/include"

# Créer le répertoire bin s'il n'existe pas
mkdir -p ./bin

# Compiler tous les fichiers source dans le répertoire src avec les chemins d'OpenCV et RapidJSON
g++ -I${OPENCV_INCLUDE_DIR} -I${RAPIDJSON_INCLUDE_DIR} -L${OPENCV_LIB_DIR} ./src/*.cpp -o ./bin/main -lopencv_world460

# Exécuter le fichier compilé
./bin/main