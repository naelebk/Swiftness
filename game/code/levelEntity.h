#ifndef LEVEL_ENTITY_H
#define LEVEL_ENTITY_H


#include "levelData.h"
#include "squareEntity.h"

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
        LevelData& getLevelEntity() { return m_levelData; };

        

        /**
         * @brief Get the name of the tmx file
         *
         * @return std::string the name of the tmx file
         */
        std::string getNameFile() { return m_name; };

    private:
        std::string m_name;
        LevelData m_levelData;
        Square m_squareEntity;

        
    };

} // namespace swiftness

#endif // LEVEL_ENTITY_H

