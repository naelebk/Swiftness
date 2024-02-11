#include "levelGenerator.h"

namespace swiftness
{

    LevelGenerator::LevelGenerator(gf::ResourceManager& resources, std::string nameFile)
        : m_nameFile(nameFile), m_levelData(nameFile), m_squareEntity(resources, m_levelData.getEntrance(), SQUARE_SIZE, gf::Color::Red, GRAVITY), m_plateforms()
    {
        m_plateforms = initializePlateforms();
        std::cout << swiftness::YELLOW << "LevelGenerator for " << nameFile << "\t\t[LOADED]\n" << swiftness::NC << std::endl;
    }

    void LevelGenerator::resetLevel()
    {
        m_squareEntity.reset(m_levelData.getEntrance());
    }

    std::vector<swiftness::PlateformEntity> LevelGenerator::generateVerticalPlateform(LayerName layerName, std::vector<swiftness::PlateformEntity> verticalPlateforms)
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
                        PlateformEntity plateform = PlateformEntity(position, height, length, gf::Color::Blue);
                        if (color)
                        {
                            plateform = PlateformEntity(position, height, length, gf::Color::Yellow);
                        }
                        verticalPlateforms.push_back(plateform);
                    }
                    y++;
                }
            }
        }
        return verticalPlateforms;
    }

    std::vector<swiftness::PlateformEntity> LevelGenerator::generateHorizontalPlateform(LayerName layerName, std::vector<swiftness::PlateformEntity> horizontalPlateforms)
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
                        PlateformEntity plateform = PlateformEntity(position, height, length, gf::Color::Blue);
                        if (color)
                        {
                            plateform = PlateformEntity(position, height, length, gf::Color::Yellow);
                        }
                        horizontalPlateforms.push_back(plateform);
                    }
                    x++;
                }
            }
        }
        return horizontalPlateforms;
    }

    std::vector<swiftness::PlateformEntity> LevelGenerator::generateBlocPlateforms(LayerName layerName, std::vector<swiftness::PlateformEntity> blocPlateforms)
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

                        PlateformEntity plateform = PlateformEntity(position, height, length, gf::Color::Blue);
                        if (color)
                        {
                            plateform = PlateformEntity(position, height, length, gf::Color::Yellow);
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
                    }
                }
            }
        }
        return blocPlateforms;
    }

    std::vector<swiftness::PlateformEntity> LevelGenerator::generateBorder(std::vector<swiftness::PlateformEntity> invisiblePlateforms)
    {

        gf::TmxTileLayer *layer = m_levelData.getLayersEntity().getTileLayerByName(LayerName::Border);
        std::vector<gf::TmxCell> cells = m_levelData.getLayersEntity().getCellsOfaLayer(LayerName::Border);
        gf::Vector2f mapSize = m_levelData.getMapSize();
        gf::Vector2f tileSize = m_levelData.getTileSize();

        if (layer)
        {

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
                        PlateformEntity plateform = PlateformEntity(position, height, length, gf::Color::Transparent);
                        invisiblePlateforms.push_back(plateform);

                        // Marquer les cellules déjà traitées
                        for (int ix = x; ix <= xEnd; ix++)
                        {
                            for (int iy = y; iy <= yEnd; iy++)
                            {
                                cells[ix + iy * mapSize.width].gid = 0;
                            }
                        }
                    }
                }
            }
        }
        return invisiblePlateforms;
    }

    std::vector<swiftness::PlateformEntity> LevelGenerator::generateGravitySwitchs(std::vector<swiftness::PlateformEntity> gravitySwitchs)
    {
        std::vector<std::unique_ptr<gf::TmxObject>> objects = m_levelData.getLayersEntity().getObjectsOfaLayer(LayerName::gravity_switch);

        for (const auto &objPtr : objects)
        {
            if (objPtr->visible)
            {
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
                    gf::Vector2f position = objPtr.get()->position;
                    position.x += width / 2;
                    position.y += height / 2;
                    PlateformEntity plateform(position, height, width, color);
                    gravitySwitchs.push_back(plateform);
                }
            }
        }
        return gravitySwitchs;
    }

    std::vector<swiftness::PlateformEntity> LevelGenerator::generateGravityWalls(std::vector<swiftness::PlateformEntity> gravityWalls)
    {
        std::vector<std::unique_ptr<gf::TmxObject>> objects = m_levelData.getLayersEntity().getObjectsOfaLayer(LayerName::gravity_walls);

        for (const auto &objPtr : objects)
        {
            gf::TmxRectangle *rect = static_cast<gf::TmxRectangle *>(objPtr.get());
            if (objPtr)
            {
                gf::Color4f color;
                if (objPtr.get()->type == "down")
                {
                    color = gf::Color::fromRgb(100, 100, 10);
                }
                else if (objPtr.get()->type == "up")
                {
                    color = gf::Color::fromRgb(100, 100, 20);
                }
                else if (objPtr.get()->type == "left")
                {
                    color = gf::Color::fromRgb(100, 100, 30);
                }
                else if (objPtr.get()->type == "right")
                {
                    color = gf::Color::fromRgb(100, 100, 40);
                }
                int width = rect->size.width;
                int height = rect->size.height;
                gf::Vector2f position = objPtr.get()->position;
                position.x += width / 2;
                position.y += height / 2;
                PlateformEntity plateform(position, height, width, color);
                gravityWalls.push_back(plateform);
            }
        }
        return gravityWalls;
    }

    std::vector<swiftness::PlateformEntity> LevelGenerator::generateExit(std::vector<swiftness::PlateformEntity> exit)
    {
        gf::Vector2f position = m_levelData.getExit();
        int width = m_levelData.getTileSize().width;
        int height = m_levelData.getTileSize().height;
        position.x += width / 2;
        PlateformEntity plateform(position, height, width, gf::Color::Black);
        exit.push_back(plateform);
        return exit;
    }

    std::vector<swiftness::PlateformEntity> LevelGenerator::initializePlateforms() 
    {
        std::vector<swiftness::PlateformEntity> plateform;
        plateform = generateVerticalPlateform(LayerName::Collision_v,plateform);
        std::cout << swiftness::BOLD << "Vertical plateform\t[GENERATED]" << std::endl;
        

        // Ajout des plateformes horizontales
        plateform = generateHorizontalPlateform(LayerName::Collision_h,plateform);
        std::cout << "Horizontal plateform\t[GENERATED]" << std::endl;
        

        // Ajout des plateformes bloc
        plateform = generateBlocPlateforms(LayerName::Collision_bloc,plateform);
        std::cout << "Bloc plateform\t\t[GENERATED]" << std::endl;
        
        // Ajout des plateformes tueuses !!

        // Ajout des plateformes verticales
        plateform = generateVerticalPlateform(LayerName::Wall_of_death_v,plateform);
        std::cout << "Vertical death\t\t[GENERATED]" << std::endl;
        

        // Ajout des plateformes horizontales
        plateform = generateHorizontalPlateform(LayerName::Wall_of_death_h,plateform);
        std::cout << "Horizontal death\t[GENERATED]" << std::endl;
        

        // Ajout des plateformes bloc
        plateform = generateBlocPlateforms(LayerName::Wall_of_death_bloc,plateform);
        std::cout << "Bloc death\t\t[GENERATED]" << std::endl;
        

        // Ajout des gravity switch
        plateform = generateGravitySwitchs(plateform);
        std::cout << "Gravity switch\t\t[GENERATED]" << std::endl;
        

        // ajout des murs invisible
        plateform = generateBorder(plateform);
        std::cout << "Border\t\t\t[GENERATED]" << std::endl;

        // Ajout des gravity walls
        plateform = generateGravityWalls(plateform);
        std::cout << "Gravity wall\t\t[GENERATED]" << std::endl;

        // Ajout de la sortie
        plateform = generateExit(plateform);
        std::cout << "Exit\t\t\t[GENERATED]" << swiftness::NC << std::endl;

        return plateform;
    }

} // namespace swiftness
