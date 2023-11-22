#include "levelData.h"

namespace hg {

    LevelData::LevelData(std::string nameFile) {

        m_nameFile = nameFile;
        m_layerEntity = LayerEntity(nameFile);
        
        gf::TileLayer layer = m_layerEntity.getLayerByName("entrance");

        
    }
}