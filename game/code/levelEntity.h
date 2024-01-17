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
        std::map<int, StaticPlateform> generateVerticalPlateform(int index, LayerName layerName);

        /**
         * @brief generate the horizontal plateform
         *
         * @return std::map<int, StaticPlateform> the horizontal plateform
         */
        std::map<int, StaticPlateform> generateHorizontalPlateform(int index, LayerName layerName);

        /**
         * @brief generate the bloc plateform
         * 
         * @param index 
         * 
         * @return std::map<int, StaticPlateform> the bloc plateform
         */
        std::map<int, StaticPlateform> generateBlocPlateforms(int index, LayerName layerName);

        /**
         * @brief generate Border of the map
         * 
         * @param index
         * 
         * @return std::map<int, StaticPlateform> the Border of the map
         */
        std::map<int, StaticPlateform> generateBorder(int index);

        /**
         * @brief generate the gravtiy switchs
         * 
         * @param index
         * 
         * @return std::map<int, StaticPlateform> the gravity switchs
         */
        std::map<int, StaticPlateform> generateGravitySwitchs(int index);

        /**
         * @brief make a plateform for the exit
         * 
         * @return std::map<int, StaticPlateform> the plateform for the exit
         */
        std::map<int, StaticPlateform> generateExit(int index);

    private:
        std::string m_name;
        LevelData m_levelData;
        Square m_squareEntity;

        
    };

} // namespace swiftness

#endif // LEVEL_ENTITY_H

