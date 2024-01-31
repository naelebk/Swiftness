cmake_minimum_required(VERSION 3.10)
 
project(SWIFTNESS_TEST_ONE
  VERSION 0.1.0
)
 
find_package(gf REQUIRED)

add_executable(swiftness
  ./code/constants.cc
  ./code/tilesEnumData.cc
  ./code/gameCenter.cc
  ./code/main.cc
  ./code/scene/creditScene.cc
  ./code/scene/SelectLevelScene.cc
  ./code/scene/MenuScene.cc
  ./code/scene/levelScene.cc
  ./code/scene/startScene.cc
  ./code/scene/pauseScene.cc
  ./code/tmx/layerData.cc
  ./code/tmx/level.cc
  ./code/tmx/levelData.cc
  ./code/tmx/generationLevel.cc
  ./code/tmx/levelRender.cc
  ./code/entity/squareEntity.cc
  ./code/entity/plateformEntity.cc
  )

target_include_directories(swiftness
PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR})
  

 
target_link_libraries(swiftness
  PRIVATE
    gf::graphics
    gf::net
)
