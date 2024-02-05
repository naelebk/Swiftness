#include "layerData.h"

namespace swiftness
{

        LayerData::LayerData(std::string nameFile)
        {
                std::cout << swiftness::CYAN << "LayerData\t\t[LOADED]" << swiftness::NC << std::endl;
                m_layers = loadLayers(nameFile);
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
