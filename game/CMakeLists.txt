cmake_minimum_required(VERSION 3.10)
 
project(SWIFTNESS_TEST_ONE VERSION 0.1.0)
 
# Trouver le package gf
find_package(gf REQUIRED)

# Trouver le package SFML et spécifier les composants nécessaires
find_package(SFML REQUIRED COMPONENTS audio)

# Définir la cible de l'exécutable et lister tous les fichiers sources
add_executable(swiftness
  ./code/constants.cc
  ./code/gameCenter.cc
  ./code/audioManager.cc
  ./code/scene/creditScene.cc
  ./code/scene/selectLevelScene.cc
  ./code/scene/selectCustomLevelScene.cc
  ./code/scene/MenuScene.cc
  ./code/scene/levelScene.cc
  ./code/scene/startScene.cc
  ./code/scene/pauseScene.cc
  ./code/tmx/layerData.cc
  ./code/tmx/levelData.cc
  ./code/tmx/levelGenerator.cc
  ./code/tmx/levelRender.cc
  ./code/entity/squareEntity.cc
  ./code/entity/plateformEntity.cc
  ./code/main.cc
)

# Inclure les répertoires d'en-têtes
target_include_directories(swiftness PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  
# Lier les bibliothèques gf et SFML à l'exécutable
target_link_libraries(swiftness
  PRIVATE
    gf::graphics
    gf::net
    sfml-audio
)
