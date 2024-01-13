#include "levelEntity.h"

namespace swiftness
{

    LevelEntity::LevelEntity(std::string nameFile)
        : m_name(nameFile), m_levelData(nameFile), m_squareEntity(m_levelData.getEntrance(), m_levelData.getTileSize().width, gf::Color::Red, GRAVITY)
    {
        std::cout << "LevelEntity created for file: " << nameFile << std::endl;
    }

    std::map<int, StaticPlateform> LevelEntity::generateVerticalPlateform(int index, LayerName layerName)
    {
        std::map<int, StaticPlateform> verticalPlateforms;
        gf::TmxTileLayer *layer = m_levelData.getLayersEntity().getTileLayerByName(layerName);
        std::vector<gf::TmxCell> cells = m_levelData.getLayersEntity().getCellsOfaLayer(layerName);
        gf::Vector2f mapSize = m_levelData.getMapSize();
        gf::Vector2f tileSize = m_levelData.getTileSize();

        if (layer)
        {
            bool color = false;
            if (layerName == LayerName::Wall_of_death_v)
            {
                color = true;
            }
            int platformIndex = index;
            for (int x = 0; x < mapSize.width; x++)
            {
                int y = 0;
                while (y < mapSize.height)
                {
                    gf::TmxCell &cell = cells[x + y * mapSize.width];
                    if (cell.gid != 0)
                    {
                        float height = tileSize.height;
                        float length = tileSize.width;

                        while (y + 1 < mapSize.height && cells[x + (y + 1) * mapSize.width].gid != 0)
                        {
                            y++;
                            height += tileSize.height;
                        }

                        gf::Vector2f position = gf::Vector2f(x * tileSize.width + tileSize.width / 2, y * tileSize.height - height / 2 + tileSize.height);
                        StaticPlateform plateform = StaticPlateform(position, height, length, gf::Color::Blue);
                        if (color)
                        {
                            plateform = StaticPlateform(position, height, length, gf::Color::Yellow);
                        }
                        verticalPlateforms.insert(std::pair<int, StaticPlateform>(platformIndex, plateform));
                        platformIndex++;
                    }
                    y++;
                }
            }
        }
        return verticalPlateforms;
    }

    std::map<int, StaticPlateform> LevelEntity::generateHorizontalPlateform(int index, LayerName layerName)
    {
        std::map<int, StaticPlateform> horizontalPlateforms;
        gf::TmxTileLayer *layer = m_levelData.getLayersEntity().getTileLayerByName(layerName);
        std::vector<gf::TmxCell> cells = m_levelData.getLayersEntity().getCellsOfaLayer(layerName);
        gf::Vector2f mapSize = m_levelData.getMapSize();
        gf::Vector2f tileSize = m_levelData.getTileSize();

        if (layer)
        {
            bool color = false;
            if (layerName == LayerName::Wall_of_death_h)
            {
                color = true;
            }
            int platformIndex = index;
            for (int y = 0; y < mapSize.height; y++)
            {
                int x = 0;
                while (x < mapSize.width)
                {
                    gf::TmxCell &cell = cells[x + y * mapSize.width];
                    if (cell.gid != 0)
                    {
                        float height = tileSize.height;
                        float length = tileSize.width;

                        while (x + 1 < mapSize.width && cells[(x + 1) + y * mapSize.width].gid != 0)
                        {
                            x++;
                            length += tileSize.width;
                        }

                        gf::Vector2f position = gf::Vector2f(x * tileSize.width - length / 2 + tileSize.width, y * tileSize.height + tileSize.height / 2);
                        StaticPlateform plateform = StaticPlateform(position, height, length, gf::Color::Blue);
                        if (color)
                        {
                            plateform = StaticPlateform(position, height, length, gf::Color::Yellow);
                        }
                        horizontalPlateforms.insert(std::pair<int, StaticPlateform>(platformIndex, plateform));
                        platformIndex++;
                    }
                    x++;
                }
            }
        }
        return horizontalPlateforms;
    }

    std::map<int, StaticPlateform> LevelEntity::generateBlocPlateforms(int index, LayerName layerName)
    {
        std::map<int, StaticPlateform> blocPlateforms;
        gf::TmxTileLayer *layer = m_levelData.getLayersEntity().getTileLayerByName(layerName);
        std::vector<gf::TmxCell> cells = m_levelData.getLayersEntity().getCellsOfaLayer(layerName);
        gf::Vector2f mapSize = m_levelData.getMapSize();
        gf::Vector2f tileSize = m_levelData.getTileSize();

        if (layer)
        {
            bool color = false;
            if (layerName == LayerName::Wall_of_death_bloc)
            {
                color = true;
            }
            std::cout << "color : " << color << std::endl;
            int platformIndex = index;
            for (int y = 0; y < mapSize.height; y++)
            {
                for (int x = 0; x < mapSize.width; x++)
                {
                    gf::TmxCell &cell = cells[x + y * mapSize.width];
                    if (cell.gid != 0)
                    {
                        float height = tileSize.height;
                        float length = tileSize.width;

                        // Étendre vers la droite
                        int xEnd = x;
                        while (xEnd + 1 < mapSize.width && cells[(xEnd + 1) + y * mapSize.width].gid == cell.gid)
                        {
                            xEnd++;
                            length += tileSize.width;
                        }

                        // Étendre vers le bas
                        int yEnd = y;
                        while (yEnd + 1 < mapSize.height && cells[x + (yEnd + 1) * mapSize.width].gid == cell.gid)
                        {
                            yEnd++;
                            height += tileSize.height;
                        }

                        // Calculer la position centrée de la plateforme
                        gf::Vector2f position = gf::Vector2f((x + xEnd) * tileSize.width / 2 + tileSize.width / 2,
                                                             (y + yEnd) * tileSize.height / 2 + tileSize.height / 2);

                        StaticPlateform plateform = StaticPlateform(position, height, length, gf::Color::Blue);
                        if (color)
                        {
                            plateform = StaticPlateform(position, height, length, gf::Color::Yellow);
                        }
                        blocPlateforms.insert(std::pair<int, StaticPlateform>(platformIndex, plateform));

                        // Marquer les cellules déjà traitées
                        for (int ix = x; ix <= xEnd; ix++)
                        {
                            for (int iy = y; iy <= yEnd; iy++)
                            {
                                cells[ix + iy * mapSize.width].gid = 0;
                            }
                        }

                        platformIndex++;
                    }
                }
            }
        }
        return blocPlateforms;
    }

    std::map<int, StaticPlateform> LevelEntity::generateBorder(int index)
    {
        std::map<int, StaticPlateform> invisiblePlateforms;
        gf::TmxTileLayer *layer = m_levelData.getLayersEntity().getTileLayerByName(LayerName::Border);
        std::vector<gf::TmxCell> cells = m_levelData.getLayersEntity().getCellsOfaLayer(LayerName::Border);
        gf::Vector2f mapSize = m_levelData.getMapSize();
        gf::Vector2f tileSize = m_levelData.getTileSize();

        if (layer)
        {
            int platformIndex = index;
            for (int y = 0; y < mapSize.height; y++)
            {
                for (int x = 0; x < mapSize.width; x++)
                {
                    gf::TmxCell &cell = cells[x + y * mapSize.width];
                    if (cell.gid != 0)
                    {
                        float height = tileSize.height;
                        float length = tileSize.width;

                        // Étendre vers la droite
                        int xEnd = x;
                        while (xEnd + 1 < mapSize.width && cells[(xEnd + 1) + y * mapSize.width].gid == cell.gid)
                        {
                            xEnd++;
                            length += tileSize.width;
                        }

                        // Étendre vers le bas
                        int yEnd = y;
                        while (yEnd + 1 < mapSize.height && cells[x + (yEnd + 1) * mapSize.width].gid == cell.gid)
                        {
                            yEnd++;
                            height += tileSize.height;
                        }

                        // Calculer la position centrée de la plateforme
                        gf::Vector2f position = gf::Vector2f((x + xEnd) * tileSize.width / 2 + tileSize.width / 2,
                                                             (y + yEnd) * tileSize.height / 2 + tileSize.height / 2);
                        StaticPlateform plateform = StaticPlateform(position, height, length, gf::Color::Transparent);
                        invisiblePlateforms.insert(std::pair<int, StaticPlateform>(platformIndex, plateform));

                        // Marquer les cellules déjà traitées
                        for (int ix = x; ix <= xEnd; ix++)
                        {
                            for (int iy = y; iy <= yEnd; iy++)
                            {
                                cells[ix + iy * mapSize.width].gid = 0;
                            }
                        }

                        platformIndex++;
                    }
                }
            }
        }
        return invisiblePlateforms;
    }

    std::map<int, StaticPlateform> LevelEntity::generateGravitySwitchs(int index)
    {
        std::map<int, StaticPlateform> gravitySwitchs;
        std::vector<std::unique_ptr<gf::TmxObject>> objects = m_levelData.getLayersEntity().getObjectsOfaLayer(LayerName::gravity_switch);

        int platformIndex = index;
        for (const auto &objPtr : objects)
        {
            if (objPtr)
            {
                gf::Color4f color;
                if (objPtr.get()->type == "down") // Assurez-vous que la méthode getType() existe
                {
                    color = gf::Color::Rose; // Remplacez par la couleur appropriée si Rose n'existe pas
                }
                else if (objPtr.get()->type == "up")
                {
                    color = gf::Color::Cyan;
                }
                int width = objPtr.get()->properties.getIntProperty("width", 8);
                int height = objPtr.get()->properties.getIntProperty("height", 12);
                std::cout << "width : " << width << std::endl;
                std::cout << "height : " << height << std::endl;
                gf::Vector2f position = objPtr.get()->position;
                position.x += width / 2;
                position.y += height / 2;
                std::cout << "position : " << position.col << " : " << position.row << std::endl;
                StaticPlateform plateform(position, height, width, color);
                gravitySwitchs.insert(std::make_pair(platformIndex, plateform));
                platformIndex++;
            }
        }

        return gravitySwitchs;
    }

} // namespace swiftness
