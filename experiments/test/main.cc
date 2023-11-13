#include "squareEntity.h"
#include "plateforme.h"
#include "level0.cc"

#include <gf/Clock.h>
#include <gf/Color.h>
#include <gf/Event.h>
#include <gf/RenderWindow.h>
#include <gf/Shapes.h>
#include <gf/Vector.h>
#include <gf/Window.h>
#include <gf/Math.h>
#include <iostream>
#include <stdlib.h>

#define GRAVITY 100.0f
#define SPEED 200.0f

int main()
{
    // initialization
    gf::Window window("It moves", {640, 480});
    // window.setFullscreen(true);

    gf::RenderWindow renderer(window);

    // Get the screen size after setting fullscreen mode
    gf::Vector2i ScreenSize = window.getSize();

    // create a square
    hg::Square square({100.0f, 100.0f}, 20.0f, gf::Color::Red, GRAVITY);

    // create a list of plateform using the ScreenSize using level0
    std::map<int, hg::StaticPlateform> plateform = hg::initializeLevel0(ScreenSize);

    // game loop
    gf::Clock clock;
    renderer.clear(gf::Color::White);

    gf::Vector2f velocity(0, GRAVITY);

    while (window.isOpen())
    {

        gf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case gf::EventType::Closed:
                window.close();
                break;

            case gf::EventType::KeyPressed:
                switch (event.key.keycode)
                {
                case gf::Keycode::Escape:
                    window.close();
                    break;
                case gf::Keycode::Up:
                case gf::Keycode::Z:
                    velocity.y -= SPEED;
                    break;
                case gf::Keycode::Down:
                case gf::Keycode::S:
                    velocity.y += SPEED;
                    break;
                case gf::Keycode::Left:
                case gf::Keycode::Q:
                    velocity.x -= SPEED;
                    break;
                case gf::Keycode::Right:
                case gf::Keycode::D:
                    velocity.x += SPEED;
                    break;
                default:
                    break;
                }
                break;

            case gf::EventType::KeyReleased:
                switch (event.key.keycode)
                {
                case gf::Keycode::Up:
                case gf::Keycode::Z:
                    velocity.y += SPEED;
                    break;
                case gf::Keycode::Down:
                case gf::Keycode::S:
                    velocity.y -= SPEED;
                    break;
                case gf::Keycode::Left:
                case gf::Keycode::Q:
                    velocity.x += SPEED;
                    break;
                case gf::Keycode::Right:
                case gf::Keycode::D:
                    velocity.x -= SPEED;
                    break;
                default:
                    break;
                }
                break;

            default:
                break;
            }
        }

        // update the square
        float dt = clock.restart().asSeconds();
        square.setVelocity(velocity);
        // square.update(dt, plateformUp);
        // square.update(dt, plateformDown);
        // square.update(dt, plateformLeft);
        // square.update(dt, plateformRight);
        square.updateWithMap(dt, plateform);

        // render
        renderer.clear(gf::Color::White);
        square.render(renderer);
        for (auto &p : plateform)
        {
            p.second.render(renderer);
        }
        renderer.display();
    }
    return 0;
}