#include "layerData.h"
#include "constants.h"
#include "tilesEnumData.h"

namespace swiftness
{

        void LayerData::LayersMaker::visitTileLayer(const gf::TmxLayers &map, const gf::TmxTileLayer &layer)
        {
                if (!layer.visible)
                {
                        return;
                }

                std::cout << "Parsing layer '" << layer.name << "'\n";
        }

        LayerData::LayerData(std::string nameFile)
        {
                m_layers = loadLayers(nameFile);
                m_resources.addSearchDir(LEVELS_TMX_PATH);
                m_resources.addSearchDir(TILESETS_TSX_PATH);
                m_resources.addSearchDir(IMAGES_GAME);
                m_resources.addSearchDir(gf::Paths::getBasePath());
                m_resources.addSearchDir(gf::Paths::getCurrentPath());
                m_mapSize = m_layers.mapSize;
                m_tileSize = m_layers.tileSize;
        }

        gf::TmxLayers LayerData::loadLayers(std::string nameFile)
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

        gf::TmxTileLayer *LayerData::getTileLayerByName(LayerName layerName)
        {
                std::string name = getLayerName(layerName);
                if (name == "Error")
                        return nullptr;
                gf::TmxTileLayer *layerIT = nullptr;
                for (auto &layer : m_layers.layers)
                {
                        if (layer->name == name)
                        {
                                return layerIT = static_cast<gf::TmxTileLayer *>(layer.get());
                        }
                }
                return layerIT;
        }

        gf::TmxObjectLayer *LayerData::getObjectLayerByName(LayerName layerName)
        {
                std::string name = getLayerName(layerName);
                if (name == "Error")
                        return nullptr;
                gf::TmxObjectLayer *layerIT = nullptr;
                for (auto &layer : m_layers.layers)
                {
                        if (layer->name == name)
                        {
                                return layerIT = static_cast<gf::TmxObjectLayer *>(layer.get());
                        }
                }
                return layerIT;
        }

} // namespace swiftness
