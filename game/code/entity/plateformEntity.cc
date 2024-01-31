#include "plateformEntity.h"

namespace swiftness
{

    PlateformEntity::PlateformEntity(gf::Vector2f position, float height, float length, gf::Color4f color)
            : m_position(position), m_height(height), m_length(length), m_color(color)
        {
        }

    void PlateformEntity::render(gf::RenderTarget &target)
    {
        gf::RectangleShape shape({m_length, m_height});
        shape.setPosition(m_position);
        shape.setColor(m_color);
        shape.setAnchor(gf::Anchor::Center);
        target.draw(shape);
    }

    gf::Vector2f PlateformEntity::getPosition() const
    {
        return m_position;
    }

    float PlateformEntity::getHeight() const
    {
        return m_height;
    }

    float PlateformEntity::getLength() const
    {
        return m_length;
    }

    gf::Color4f PlateformEntity::getColor() const
    {
        return m_color;
    }

    void PlateformEntity::setPosition (gf::Vector2f self) {
        m_position = self;
    }

    void PlateformEntity::setHeight(float self) {
        m_height = self;
    }

    void PlateformEntity::setLength(float self) {
        m_length = self;
    }

} // namespace swiftness
