#include "levelEntity.h"
#include <iostream>

namespace swiftness {

    LevelEntity::LevelEntity(std::string nameFile)
        : m_name(nameFile), m_levelData(nameFile), m_squareEntity(m_levelData.getEntrance(), m_levelData.getTileSize().width, gf::Color::Red, GRAVITY)
    {
        // Vous pouvez initialiser d'autres membres ici si nécessaire
        std::cout << "LevelEntity created for file: " << nameFile << std::endl;
    }

    std::map<int, StaticPlateform> LevelEntity::generateVerticalPlateform() {
        std::map<int, StaticPlateform> verticalPlateforms;
        gf::TmxTileLayer* layer = m_levelData.getLayersEntity().getLayerByName(LayerName::Collision_v);
        std::vector<gf::TmxCell> cells = m_levelData.getLayersEntity().getCellsOfaLayer(LayerName::Collision_v);
        gf::Vector2i mapSize = m_levelData.getMapSize();
        gf::Vector2i tileSize = m_levelData.getTileSize();

        if (layer) {
            for (int x = 0; x < mapSize.width; x++) {
                int y = 0;
                while (y < mapSize.height) {
                    gf::TmxCell& cell = cells[x + y * mapSize.width];
                    if (cell.gid != 0) {
                        gf::Vector2f position = gf::Vector2f(x * tileSize.width, y * tileSize.height);
                        float height = tileSize.height; // Hauteur de la tuile
                        float length = tileSize.width; // Longueur de la tuile

                        // Continue à ajouter à la hauteur tant que les tuiles au-dessus sont non vides
                        while (y + 1 < mapSize.height && cells[x + (y + 1) * mapSize.width].gid != 0) {
                            y++;
                            height += tileSize.height;
                        }

                        StaticPlateform plateform = StaticPlateform(position, height, length, gf::Color::Red);
                        verticalPlateforms.insert(std::pair<int, StaticPlateform>(cell.gid, plateform));
                    }
                    y++;
                }
            }
        }
        return verticalPlateforms;
    }

    std::map<int, StaticPlateform> LevelEntity::generateHorizontalPlateform() {
        std::map<int, StaticPlateform> horizontalPlateforms;
        gf::TmxTileLayer* layer = m_levelData.getLayersEntity().getLayerByName(LayerName::Collision_h);
        std::vector<gf::TmxCell> cells = m_levelData.getLayersEntity().getCellsOfaLayer(LayerName::Collision_h);
        gf::Vector2i mapSize = m_levelData.getMapSize();
        gf::Vector2i tileSize = m_levelData.getTileSize();

        if (layer) {
            for (int y = 0; y < mapSize.height; y++) {
                int x = 0;
                while (x < mapSize.width) {
                    gf::TmxCell& cell = cells[x + y * mapSize.width];
                    if (cell.gid != 0) {
                        gf::Vector2f position = gf::Vector2f(x * tileSize.width, y * tileSize.height);
                        float height = tileSize.height; // Hauteur de la tuile
                        float length = tileSize.width; // Longueur de la tuile

                        // Continue à ajouter à la longueur tant que les tuiles à droite sont non vides
                        while (x + 1 < mapSize.width && cells[(x + 1) + y * mapSize.width].gid != 0) {
                            x++;
                            length += tileSize.width;
                        }

                        StaticPlateform plateform = StaticPlateform(position, height, length, gf::Color::Red);
                        horizontalPlateforms.insert(std::pair<int, StaticPlateform>(cell.gid, plateform));
                    }
                    x++;
                }
            }
        }
        return horizontalPlateforms;
    }

    // D'autres méthodes peuvent être implémentées ici si nécessaire

} // namespace swiftness
