cmake_minimum_required(VERSION 3.10)
 
project(SWIFTNESS_TEST_ONE
  VERSION 0.1.0
)
 
find_package(gf REQUIRED)

add_executable(game
  ./code/constants.cc
  ./code/Credits.cc
  ./code/GameCenter.cc
  ./code/SelectLevelScene.cc
  ./code/MenuScene.cc
  ./code/levelScene.cc
  ./code/layerData.cc
  ./code/level.cc
  ./code/levelData.cc
  ./code/generationLevel.cc
  ./code/levelRender.cc
  ./code/main.cc
  ./code/pauseScene.cc
  ./code/squareEntity.cc
  ./code/Start.cc
  ./code/plateformEntity.cc
  ./code/tilesEnumData.cc)

target_include_directories(game
PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR})
  

 
target_link_libraries(game
  PRIVATE
    gf::graphics
    gf::net
)
