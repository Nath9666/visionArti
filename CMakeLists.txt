cmake_minimum_required(VERSION 3.10)
project(visionArti)

# Définir le chemin vers OpenCV
set(OpenCV_DIR "C:/Users/Nathan/Documents/Projet/visionArti/opencv/build")

# Trouver le package OpenCV
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)

# Ajouter le chemin vers RapidJSON
include_directories(${CMAKE_SOURCE_DIR}/include)

# Inclure les répertoires d'en-tête
include_directories(${OpenCV_INCLUDE_DIRS})

# Ajouter les fichiers sources
file(GLOB SOURCES
    "src/*.cpp"
)

# Vérifier si des fichiers sources ont été trouvés
if(NOT SOURCES)
    message(FATAL_ERROR "Aucun fichier source trouvé dans le répertoire src")
endif()

# Ajouter l'exécutable
add_executable(visionArti ${SOURCES})

# Lier les bibliothèques nécessaires
target_link_libraries(visionArti ${OpenCV_LIBS})