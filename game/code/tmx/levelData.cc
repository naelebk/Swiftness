#include "levelData.h"

namespace swiftness
{

    LevelData::LevelData(std::string nameFile)
        : m_layerData(nameFile), m_name(nameFile)
    {
        std::cout << swiftness::PURPLE << "LevelData\t\t[LOADED]" << std::endl;
        int entrance = static_cast<int>(PlateformType::blue_portal);
        int exit = static_cast<int>(PlateformType::orange_portal);
        gf::TmxLayer *layer = m_layerData.getTileLayerByName(LayerName::IO);
        gf::TmxTileLayer *tileLayer = dynamic_cast<gf::TmxTileLayer *>(layer);
        gf::Vector2f mapSize = m_layerData.getMapSize();
        std::cout << "\t- Map Size\t: " << mapSize.x << " , " << mapSize.y << std::endl;
        gf::Vector2f tileSize = m_layerData.getTileSize();
        std::cout << "\t- Tile Size\t: " << tileSize.x << " , " << tileSize.y << std::endl;
        m_mapCenter = gf::Vector2f(mapSize.width * tileSize.width / 2, mapSize.height * tileSize.height / 2);
        std::cout << "\t- Map Center\t: " << m_mapCenter.x << " , " << m_mapCenter.y << "\n" << swiftness::NC << std::endl;
        if (tileLayer)
        {
            int stop = 0;
            for (int x = 0; x < mapSize.width; x++)
            {
                for (int y = 0; y < mapSize.height; y++)
                {
                    gf::TmxCell &cell = tileLayer->cells[x + y * mapSize.width];
                    if (cell.gid == entrance || cell.gid == exit)
                    {
                        gf::Vector2f position = gf::Vector2f(x * tileSize.width + tileSize.width / 2, y * tileSize.height + tileSize.height / 2);
                        if (cell.gid == entrance)
                        {
                            m_entrance = position;
                            stop++;
                        }
                        else if (cell.gid == exit)
                        {
                            m_exit = position;
                            stop++;
                        }
                        if (stop == 2)
                        {
                            break;
                        }
                    }
                }
                if (stop == 2)
                {
                    break;
                }
            }
        }
    }
}
