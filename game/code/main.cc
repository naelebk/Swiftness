#include "squareEntity.h"
#include "staticPlateforme.h"
#include "level.h"
#include "constants.h"
#include "commands.h"
#include "helloNewPadawan.h"

#include <gf/Clock.h>
#include <gf/Views.h>
#include <gf/View.h>
#include <gf/Color.h>
#include <gf/Event.h>
#include <gf/RenderWindow.h>
#include <gf/Shapes.h>
#include <gf/Vector.h>
#include <gf/Window.h>
#include <gf/Math.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdio.h>

using namespace swiftness;

int main(int argc, char *argv[])
{

    //std::string level = argv[1];
    // initialize the window
    std::map<int, swiftness::StaticPlateform> plateform;
    swiftness::Square square;

    // Welcome displays
    swiftness::Hello helloWorld;
    helloWorld.displayWelcomeMenu(plateform, square);
    gf::Window window("Swiftness", {WINDOW_WIDTH, WINDOW_HEIGHT});

    // set the window in fullscreen mode
    gf::RenderWindow renderer(window);

    // Get the screen size after setting fullscreen mode
    gf::Vector2i ScreenSize = window.getSize();

    // create a vector of Input
    std::vector<Input> enumVector;

    swiftness::CommandsManager commandManager;

    // initialisation of the level

    std::cout << "plateform size : " << plateform.size() << std::endl;
    // affiche les coordonnées des plateformes de la map
    for (auto &plateform : plateform)
    {
        std::cout << plateform.first << " : " << plateform.second.getPosition().x << " " << plateform.second.getPosition().y << std::endl;
    }
    // game loop
    gf::Clock clock;
    renderer.clear(gf::Color::White);

    // gf::Vector2f velocity(0, GRAVITY);
    bool isresize = false;
    while (window.isOpen())
    {

        gf::Event event;
        while (window.pollEvent(event))
        {
            commandManager.manageCommands(enumVector, event);
        }

        // update the square
        std::vector<Input>::iterator it1 = std::find(enumVector.begin(), enumVector.end(), Input::Escape);
        std::vector<Input>::iterator it2 = std::find(enumVector.begin(), enumVector.end(), Input::Closed);
        // Si on a pressé une de ces deux touches, on ferme la fenêtre de jeux
        if (it1 != enumVector.end() || it2 != enumVector.end())
            window.close();
        float dt = clock.restart().asSeconds();
        square.updateWithMap(dt, plateform, enumVector);
        gf::ExtendView camera(square.getPosition(), {SCREEN_WIDTH, SCREEN_HEIGHT});
        enumVector.clear();
        if (isresize)
        {
            isresize = false;
            gf::RenderWindow renderer(window);
        }
        // render
        renderer.clear(gf::Color::White);
        renderer.setView(camera);
        square.render(renderer);
        for (auto &plateform : plateform)
        {
            plateform.second.render(renderer);
        }
        square.renderHUD(renderer,SCREEN_WIDTH,SCREEN_HEIGHT);
        renderer.display();
    }
    return 0;
}