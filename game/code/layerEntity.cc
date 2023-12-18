#include "layerEntity.h"
#include "constants.h"
#include "tilesEnumData.h"

namespace swiftness
{

        void LayerEntity::LayersMaker::visitTileLayer(const gf::TmxLayers &map, const gf::TmxTileLayer &layer)
        {
                if (!layer.visible)
                {
                        return;
                }

                std::cout << "Parsing layer '" << layer.name << "'\n";
        }

        LayerEntity::LayerEntity(std::string nameFile)
        {
                m_layers = loadLayers(nameFile);
                m_resources.addSearchDir(LEVELS_TMX_PATH);
                m_mapSize = m_layers.mapSize;
                m_tileSize = m_layers.tileSize;
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

        gf::TmxTileLayer *LayerEntity::getLayerByName(LayerName layerName)
        {
                std::string name = getLayerName(layerName);
                if (name == "Error")
                        return nullptr;

                gf::TmxTileLayer *layerIT = nullptr;
                for (auto &layer : m_layers.layers)
                {
                        if (layer->name == name)
                        {
                                return layerIT;
                        }
                }
                return layerIT;
        }

} // namespace swiftness
