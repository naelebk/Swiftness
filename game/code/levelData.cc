#include "levelData.h"

namespace swiftness
{

    LevelData::LevelData(std::string nameFile)
        : m_layerEntity(nameFile), m_name(nameFile)
    {
        int entrance = getTileType(PlateformType::entrance);
        int exit = getTileType(PlateformType::exit);
        gf::TmxLayer* layer = m_layerEntity.getLayerByName(LayerName::IO);
        gf::TmxTileLayer* tileLayer = dynamic_cast<gf::TmxTileLayer*>(layer);
        gf::Vector2i mapSize = m_layerEntity.getMapSize();
        gf::Vector2i tileSize = m_layerEntity.getTileSize();
        if (tileLayer) {
            int stop = 0;
            for (int x = 0; x < mapSize.width; x++) {
                for (int y = 0; y < mapSize.height; y++) {
                    // 
                    gf::TmxCell& cell = tileLayer->cells[x + y * mapSize.width];
                    if (cell.gid == entrance) {
                        m_entrance = gf::Vector2i(x, y);
                        stop++;
                        if (stop == 2) {
                            break;
                        }
                    }
                    if (cell.gid == exit) {
                        m_exit = gf::Vector2i(x, y);
                        stop++;
                        if (stop == 2) {
                            break;
                        }
                    }
                }
            }
        }
    }
}