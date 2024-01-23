cmake_minimum_required(VERSION 3.10)
 
project(SWIFTNESS_TEST_ONE
  VERSION 0.1.0
)
 
find_package(gf REQUIRED)

add_executable(game
  ./code/commands.cc
  ./code/constants.cc
  ./code/GameCenter.cc
  ./code/GameLevel.cc
  ./code/MenuScene.cc
  ./code/helloNewPadawan.cc
  ./code/layerEntity.cc
  ./code/level.cc
  ./code/levelData.cc
  ./code/levelEntity.cc
  ./code/levelRender.cc
  ./code/main.cc
  ./code/squareEntity.cc
  ./code/staticPlateforme.cc
  ./code/tilesEnumData.cc)

target_include_directories(game
PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR})
  

 
target_link_libraries(game
  PRIVATE
    gf::graphics
    gf::net
)
