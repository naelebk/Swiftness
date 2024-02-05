#pragma once
#ifndef PLATEFORM_ENTITY_H
#define PLATEFORM_ENTITY_H

#include <gf/Vector.h>
#include <gf/Color.h>
#include <gf/RenderTarget.h>
#include <gf/Shapes.h>
#include <gf/Entity.h>

namespace swiftness
{
    class PlateformEntity : public gf::Entity
    {
    public:
        PlateformEntity(gf::Vector2f position, float height, float length, gf::Color4f color);

        void render(gf::RenderTarget &target, const gf::RenderStates &states) override;

        gf::Vector2f getPosition() const;

        float getHeight() const;

        float getLength() const;

        gf::Color4f getColor() const;

        void setPosition (gf::Vector2f self);

        void setHeight(float self);

        void setLength(float self);

    private:
        gf::Vector2f m_position; // Centre du carré
        float m_height;
        float m_length;
        gf::Color4f m_color;
    };
}

#endif // PLATFORM_ENTITY_H