#include "layerEntity.h"
#include "constants.h"
#include "tilesEnumData.h"

namespace hg
{

        void LayerEntity::LayersMaker::visitTileLayer(const gf::TmxLayers &map, const gf::TmxTileLayer &layer) override
        {
                if (!layer.visible)
                {
                        return;
                }

                std::cout << "Parsing layer '" << layer.name << "'\n";
        }

        LayerEntity::LayerEntity(std::string nameFile) : m_layers(loadLayers(nameFile)), m_entrance(0, 0), m_exit(0, 0)
        {

                m_layers.visitLayers(LayersMaker());
                m_entrance = m_layers.getLayerByName("IO").getTilePosition(1, 0);
                m_exit = m_layers.getLayerByName("IO").getTilePosition(2, 0);
        }

        gf::TmxLayers LayerEntity::loadLayers(std::string nameFile)
        {

                gf::TmxLayers layers;

                // Load the TMX file using the name of the file and the constant LEVELS_TMX_PATH
                if (!layers.loadFromFile(LEVELS_TMX_PATH + nameFile))
                {
                        gf::Log::error("Failed to load TMX file: %s\n", nameFile.c_str());
                        // Handle the error as needed (e.g., return an empty layers object or throw an exception)
                }

                return layers;
        }

        gf::TileLayer LayerEntity::getLayerByName(std::string name)
        {
                int id = 0;
                /*
                Collision_v = 20,
                Collision_h = 1,
                Collision_bloc = 25,
                CollisionWallWalk = 17,
                Filling = 16,
                Decoration = 3,
                Power = 18,
                Button = 19,
                IO = 26
                */
                if (name == "IO")
                {
                        id = static_cast<int>(hg::LayerName::IO);
                }
                else if (name == "Button")
                {
                        id = static_cast<int>(hg::LayerName::Button);
                }
                else if (name == "Power")
                {
                        id = static_cast<int>(hg::LayerName::Power);
                }
                else if (name == "Decoration")
                {
                        id = static_cast<int>(hg::LayerName::Decoration);
                }
                else if (name == "Filling")
                {
                        id = static_cast<int>(hg::LayerName::Filling);
                }
                else if (name == "CollisionWallWalk")
                {
                        id = static_cast<int>(hg::LayerName::CollisionWallWalk);
                }
                else if (name == "Collision_bloc")
                {
                        id = static_cast<int>(hg::LayerName::Collision_bloc);
                }
                else if (name == "Collision_h")
                {
                        id = static_cast<int>(hg::LayerName::Collision_h);
                }
                else if (name == "Collision_v")
                {
                        id = static_cast<int>(hg::LayerName::Collision_v);
                }
                else
                {
                        gf::Log::error("Failed to get layer: %s\n", name.c_str());
                }

                return getLayerByID(id);
        }

        gf::TileLayer LayerEntity::getLayerByID(int id)
        {       
        }

} // namespace hg
