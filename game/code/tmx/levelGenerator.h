#pragma once
#ifndef LEVEL_GENERATOR_H
#define LEVEL_GENERATOR_H


#include "levelData.h"
#include "../entity/squareEntity.h"
#include "../constants.h"
#include <iostream>
namespace swiftness
{

    class LevelGenerator
    {
    public:
        LevelGenerator(std::string nameFile);

        /**
         * @brief Load a tmx file
         *
         * @return gf::TmxLayers the layers of the tmx file
         */
        LevelData& getLevelData() { return m_levelData; };

        /**
         * @brief Get the square of the level
         *
         * @return Square the square of the level
         */
        Square& getSquareEntity() { return m_squareEntity; };

        

        /**
         * @brief Get the name of the tmx file
         *
         * @return std::string the name of the tmx file
         */
        std::string getNameFile() { return m_name; };

        /**
         * @brief generate the vertical plateform
         *
         * @return std::map<int, StaticPlateform> the vertical plateform
         */
        std::vector<swiftness::PlateformEntity> generateVerticalPlateform(int index, LayerName layerName, std::vector<swiftness::PlateformEntity> verticalPlateforms);

        /**
         * @brief generate the horizontal plateform
         *
         * @return std::map<int, StaticPlateform> the horizontal plateform
         */
        std::vector<swiftness::PlateformEntity> generateHorizontalPlateform(int index, LayerName layerName, std::vector<swiftness::PlateformEntity> horizontalPlateforms);

        /**
         * @brief generate the bloc plateform
         * 
         * @param index 
         * 
         * @return std::map<int, StaticPlateform> the bloc plateform
         */
        std::vector<swiftness::PlateformEntity> generateBlocPlateforms(int index, LayerName layerName, std::vector<swiftness::PlateformEntity> blocPlateforms);

        /**
         * @brief generate Border of the map
         * 
         * @param index
         * 
         * @return std::map<int, StaticPlateform> the Border of the map
         */
        std::vector<swiftness::PlateformEntity> generateBorder(int index,std::vector<swiftness::PlateformEntity> invisiblePlateforms);

        /**
         * @brief generate the gravtiy switchs
         * 
         * @param index
         * 
         * @return std::map<int, StaticPlateform> the gravity switchs
         */
        std::vector<swiftness::PlateformEntity> generateGravitySwitchs(int index,std::vector<swiftness::PlateformEntity> gravitySwitchs);

        /**
         * @brief make a plateform for the exit
         * 
         * @return std::map<int, StaticPlateform> the plateform for the exit
         */
        std::vector<swiftness::PlateformEntity> generateExit(int index,std::vector<swiftness::PlateformEntity> exit);

        /**
         * @brief generate the gravity walls
         * 
         * @param index
         * 
         * @return std::map<int, StaticPlateform> the gravity walls
         */
        std::vector<swiftness::PlateformEntity> generateGravityWalls(int index,std::vector<swiftness::PlateformEntity> gravityWalls);

    private:
        std::string m_name;
        LevelData m_levelData;
        Square m_squareEntity;

        
    };

} // namespace swiftness

#endif // LEVEL_GENERATOR_H

