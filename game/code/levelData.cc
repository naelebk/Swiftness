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
        gf::Vector2f mapSize = m_layerEntity.getMapSize();
        std::cout << "mapSize: " << mapSize.x << " , " << mapSize.y << std::endl;
        gf::Vector2f tileSize = m_layerEntity.getTileSize();
        std::cout << "tileSize: " << tileSize.x << " , " << tileSize.y << std::endl;
        m_mapCenter = gf::Vector2f(mapSize.width * tileSize.width / 2, mapSize.height * tileSize.height / 2);
        std::cout << "mapCenter: " << m_mapCenter.x << " , " << m_mapCenter.y << std::endl;
        if (tileLayer) {
            int stop = 0;
            for (int x = 0; x < mapSize.width; x++) {
                for (int y = 0; y < mapSize.height; y++) {
                    // 
                    gf::TmxCell& cell = tileLayer->cells[x + y * mapSize.width];
                    if (cell.gid == entrance) {
                        m_entrance = gf::Vector2f(x, y);
                        stop++;
                        if (stop == 2) {
                            break;
                        }
                    }
                    if (cell.gid == exit) {
                        m_exit = gf::Vector2f(x, y);
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