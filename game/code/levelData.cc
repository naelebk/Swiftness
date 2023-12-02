#include "levelData.h"

namespace swiftness
{

    LevelData::LevelData(std::string nameFile)
        : m_layerEntity(nameFile), m_nameFile(nameFile)
    {
        m_entrance = m_layerEntity.getEntrance();
        m_exit = m_layerEntity.getExit();
    }
}