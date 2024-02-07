#pragma once
#ifndef SQUARE_ENTITY_H
#define SQUARE_ENTITY_H

#include <gf/Vector.h>
#include <gf/Color.h>
#include <gf/Color.h>
#include <gf/RenderTarget.h>
#include <gf/Shapes.h>
#include <gf/Window.h>
#include <gf/Math.h>
#include <gf/Event.h>
#include <gf/Font.h>
#include <gf/Text.h>
#include <gf/Texture.h>
#include <gf/Entity.h>
#include <gf/Time.h>
#include <map>
#include <vector>
#include <gf/Views.h>
#include <iostream>
#include <gf/ResourceManager.h>
#include <gf/Action.h>
#include "plateformEntity.h"
#include "../constants.h"

namespace swiftness
{
    class Square : public gf::Entity
    {
    public:
        /**
         * default constructor
        */
        Square() = default;
        
        /**
         * @brief Construct a new Square object
         *
         * @param position
         * @param size
         * @param color
         * @param gravity
         */
        Square(gf::Vector2f position, float size, gf::Color4f color, float gravity);

        void copyFrom(const Square& other);

        /**
         * @brief Récupère la position du carré
        */
        gf::Vector2f getPosition() const;

        float getSize() const { return m_size; };

        /**
         * @brief Définit la vitesse du carré
        */
        void setVelocity(gf::Vector2f velocity);

        /**
         * @brief Met à jour la position du carré
        */
        void update(gf::Time dt) override;

        /**
        * Méthode permettant de faire les actions que l'on souhaite avec les inputs
        */
        void actionUp();
        void actionUpJump();
        void actionUpRelease();
        void actionDown();
        void actionDownRelease();
        void actionLeft();
        void actionLeftJump();
        void actionLeftRelease();
        void actionRight();
        void actionRightJump();
        void actionRightRelease();
        void actionJump();
        void squareReset();

        bool isPlateform(swiftness::PlateformEntity plateform);
        /**
        * Méthode permettant de savoir si on peut sauter
        */
        bool canJump();

        bool canWallJumpRight();

        bool canWallJumpLeft();

        bool canWallJumpUp();

        bool canWallJumpDown();

        /**
         * @brief Affiche le carré
        */
        void render(gf::RenderTarget &target, const gf::RenderStates& states) override;

        /**
         * @brief Affiche le HUD du carré
        */
        void renderHUD(gf::RenderTarget &target,float width,float height,gf::Vector2f pos);

        bool getLevelOver() { return isOver; };

        int getNbDeaths() { return nb_deaths; };

        float getTimer() { return timer; };

        std::string getGravity() { return m_gravityDirection; };

        void setPlateforms(std::vector<swiftness::PlateformEntity> plateforms) { m_plateforms=plateforms;};

        void setIsFlying(bool isFlying);


        /**
         * @brief Gère les collisions avec la plateforme
        */
        void collideWithPlateform(gf::Vector2f plateformPosition, float plateformHeight, float plateformLength,gf::Color4f color,bool wallLeft,bool wallRight,bool wallDown,bool wallUp,float dt);

    private:
        gf::Vector2f m_position, m_position_start; // Centre du carré
        gf::Vector2f m_velocity;
        float m_size;
        gf::Color4f m_color;
        float gravity;
        std::string m_gravityDirection;
        bool m_jump;
        int nb_jumps;
        float m_walljump;
        int m_gravity;
        bool horizontal_g;
        bool goLeft;
        bool goRight;
        bool goUp;
        bool goDown;
        bool isOver;
        int nb_deaths;
        float timer;
        std::vector<swiftness::PlateformEntity> m_plateforms;
        bool m_isFlying;

        // graphics
        bool m_faceDirection;
        float m_rotation;
    };
}

#endif // SQUARE_ENTITY_H