cmake_minimum_required(VERSION 3.10)
project(LegoTracker)

# Définir le chemin vers OpenCV
set(OpenCV_DIR "./opencv/build")

# Trouver le package OpenCV
find_package(OpenCV REQUIRED)

# Inclure les répertoires d'en-tête
include_directories(${OpenCV_INCLUDE_DIRS})

# Ajouter les fichiers sources
file(GLOB SOURCES
    src/*.cpp
)

# Ajouter l'exécutable
add_executable(LegoTracker ${SOURCES})

# Lier les bibliothèques nécessaires
target_link_libraries(LegoTracker ${OpenCV_LIBS})

# Ajouter des modèles d'apprentissage automatique si nécessaire
# add_custom_target(train_model COMMAND python models/model_training.py)