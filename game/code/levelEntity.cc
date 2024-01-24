#include "levelEntity.h"

namespace swiftness
{

    LevelEntity::LevelEntity(std::string nameFile)
        : m_name(nameFile), m_levelData(nameFile), m_squareEntity(m_levelData.getEntrance(), SQUARE_SIZE, gf::Color::Red, GRAVITY)
    {
        std::cout << "LevelEntity created for file: " << nameFile << std::endl;
    }

    std::vector<swiftness::StaticPlateform> LevelEntity::generateVerticalPlateform(int index, LayerName layerName, std::vector<swiftness::StaticPlateform> verticalPlateforms)
    {
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
                        verticalPlateforms.push_back(plateform);
                        platformIndex++;
                    }
                    y++;
                }
            }
        }
        return verticalPlateforms;
    }

    std::vector<swiftness::StaticPlateform> LevelEntity::generateHorizontalPlateform(int index, LayerName layerName, std::vector<swiftness::StaticPlateform> horizontalPlateforms)
    {
        
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
                        horizontalPlateforms.push_back(plateform);
                        platformIndex++;
                    }
                    x++;
                }
            }
        }
        return horizontalPlateforms;
    }

    std::vector<swiftness::StaticPlateform> LevelEntity::generateBlocPlateforms(int index, LayerName layerName, std::vector<swiftness::StaticPlateform> blocPlateforms)
    {
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
                        blocPlateforms.push_back(plateform);

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

    std::vector<swiftness::StaticPlateform> LevelEntity::generateBorder(int index,std::vector<swiftness::StaticPlateform> invisiblePlateforms)
    {
    
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
                        invisiblePlateforms.push_back(plateform);

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

    std::vector<swiftness::StaticPlateform> LevelEntity::generateGravitySwitchs(int index,std::vector<swiftness::StaticPlateform> gravitySwitchs)
    {
        std::vector<std::unique_ptr<gf::TmxObject>> objects = m_levelData.getLayersEntity().getObjectsOfaLayer(LayerName::gravity_switch);

        int platformIndex = index;
        for (const auto &objPtr : objects)
        {
            if (objPtr->visible) {
                gf::TmxRectangle *rect = static_cast<gf::TmxRectangle *>(objPtr.get());
                if (objPtr)
                {
                    gf::Color4f color;
                    if (objPtr.get()->type == "down")
                    {
                        color = gf::Color::Rose;
                    }
                    else if (objPtr.get()->type == "up")
                    {
                        color = gf::Color::Cyan;
                    }
                    else if (objPtr.get()->type == "left")
                    {
                        color = gf::Color::Green;
                    }
                    else if (objPtr.get()->type == "right")
                    {
                        color = gf::Color::Orange;
                    }
                    int width = rect->size.width;
                    int height = rect->size.height;
                    std::cout << "width : " << width << std::endl;
                    std::cout << "height : " << height << std::endl;
                    gf::Vector2f position = objPtr.get()->position;
                    position.x += width / 2;
                    position.y += height / 2;
                    std::cout << "position : " << position.col << " : " << position.row << std::endl;
                    StaticPlateform plateform(position, height, width, color);
                    gravitySwitchs.push_back(plateform);
                    platformIndex++;
                }
            }
        }
        return gravitySwitchs;

    }

    std::vector<swiftness::StaticPlateform> LevelEntity::generateGravityWalls(int index,std::vector<swiftness::StaticPlateform> gravityWalls)
    {
        std::vector<std::unique_ptr<gf::TmxObject>> objects = m_levelData.getLayersEntity().getObjectsOfaLayer(LayerName::gravity_walls);

        int platformIndex = index;
        for (const auto &objPtr : objects)
        {
            gf::TmxRectangle *rect = static_cast<gf::TmxRectangle *>(objPtr.get());
            if (objPtr)
            {
                gf::Color4f color;
                if (objPtr.get()->type == "down")
                {
                    color = gf::Color::fromRgb(100,100,10);
                }
                else if (objPtr.get()->type == "up")
                {
                    color = gf::Color::fromRgb(100,100,20);
                }
                else if (objPtr.get()->type == "left")
                {
                    color = gf::Color::fromRgb(100,100,30);
                }
                else if (objPtr.get()->type == "right")
                {
                    color = gf::Color::fromRgb(100,100,40);
                }
                int width = rect->size.width;
                int height = rect->size.height;
                std::cout << "width : " << width << std::endl;
                std::cout << "height : " << height << std::endl;
                gf::Vector2f position = objPtr.get()->position;
                position.x += width / 2;
                position.y += height / 2;
                std::cout << "position : " << position.col << " : " << position.row << std::endl;
                StaticPlateform plateform(position, height, width, color);
                gravityWalls.push_back(plateform);
                platformIndex++;
            }
        }
        return gravityWalls;
    }

    std::vector<swiftness::StaticPlateform> LevelEntity::generateExit(int index, std::vector<swiftness::StaticPlateform> exit) {
        gf::Vector2f position = m_levelData.getExit();
        int width = m_levelData.getTileSize().width;
        int height = m_levelData.getTileSize().height;
        position.x += width / 2;
        StaticPlateform plateform(position, height, width, gf::Color::Black);
        exit.push_back(plateform);
        return exit;
    }

} // namespace swiftness
