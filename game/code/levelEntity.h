#pragma once
#ifndef LEVEL_ENTITY_H
#define LEVEL_ENTITY_H


#include "levelData.h"
#include "squareEntity.h"
#include "constants.h"
#include <iostream>
namespace swiftness
{

    class LevelEntity
    {
    public:
        LevelEntity(std::string nameFile);

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
        Square getSquareEntity() { return m_squareEntity; };

        

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
        std::vector<swiftness::StaticPlateform> generateVerticalPlateform(int index, LayerName layerName, std::vector<swiftness::StaticPlateform> verticalPlateforms);

        /**
         * @brief generate the horizontal plateform
         *
         * @return std::map<int, StaticPlateform> the horizontal plateform
         */
        std::vector<swiftness::StaticPlateform> generateHorizontalPlateform(int index, LayerName layerName, std::vector<swiftness::StaticPlateform> horizontalPlateforms);

        /**
         * @brief generate the bloc plateform
         * 
         * @param index 
         * 
         * @return std::map<int, StaticPlateform> the bloc plateform
         */
        std::vector<swiftness::StaticPlateform> generateBlocPlateforms(int index, LayerName layerName, std::vector<swiftness::StaticPlateform> blocPlateforms);

        /**
         * @brief generate Border of the map
         * 
         * @param index
         * 
         * @return std::map<int, StaticPlateform> the Border of the map
         */
        std::vector<swiftness::StaticPlateform> generateBorder(int index,std::vector<swiftness::StaticPlateform> invisiblePlateforms);

        /**
         * @brief generate the gravtiy switchs
         * 
         * @param index
         * 
         * @return std::map<int, StaticPlateform> the gravity switchs
         */
        std::vector<swiftness::StaticPlateform> generateGravitySwitchs(int index,std::vector<swiftness::StaticPlateform> gravitySwitchs);

        /**
         * @brief make a plateform for the exit
         * 
         * @return std::map<int, StaticPlateform> the plateform for the exit
         */
        std::vector<swiftness::StaticPlateform> generateExit(int index,std::vector<swiftness::StaticPlateform> exit);

        /**
         * @brief generate the gravity walls
         * 
         * @param index
         * 
         * @return std::map<int, StaticPlateform> the gravity walls
         */
        std::vector<swiftness::StaticPlateform> generateGravityWalls(int index,std::vector<swiftness::StaticPlateform> gravityWalls);

    private:
        std::string m_name;
        LevelData m_levelData;
        Square m_squareEntity;

        
    };

} // namespace swiftness

#endif // LEVEL_ENTITY_H

