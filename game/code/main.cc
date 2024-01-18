#include "squareEntity.h"
#include "staticPlateforme.h"
#include "level.h"
#include "constants.h"
#include "commands.h"
#include "helloNewPadawan.h"
#include "levelRender.h"

#include <memory>
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
#include <thread>
#include <chrono>

using namespace swiftness;
using std::this_thread::sleep_for;

int main(int argc, char *argv[]) {
    // Initialize everything

    // gf::Vector2f velocity(0, GRAVITY);
    bool isresize = false;
    int level = -2;
    while (true) {
        std::map<int, swiftness::StaticPlateform> plateform;
        swiftness::Square square;
        gf::Font font(PATH_FONT);
        gf::Window win1("Welcome to Swiftness", gf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));
        gf::RenderWindow renderer(win1);
        swiftness::MenuHello helloWorld(font, win1);
        while (level == -2) {
            if(helloWorld.displayLevelSelection(renderer, win1, font, level)) break;
        }            
        win1.close();
        helloWorld.loadLevelWithOrWithoutTMX(plateform, square, level);
        if (level == -1) break;
        std::cout << "Level : " << level << '\n';
        std::string lvl = "";
        if (level >= 0 && level < 10) {
            lvl = "level0" + std::to_string(level) + ".tmx";
        } else {
            lvl = "level" + std::to_string(level) + ".tmx";
        }
        swiftness:LevelData ldata(lvl);
        float map_width=ldata.getMapSize().x;
        float map_height=ldata.getMapSize().y;
        float tile_width=ldata.getTileSize().x;
        float tile_height=ldata.getTileSize().y;
        gf::Window window("Swiftness", gf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));
        gf::RenderWindow render(window);  

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
        render.clear(gf::Color::Black);
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
            if (it1 != enumVector.end() || it2 != enumVector.end()) {
                window.close();
            }
            float dt = clock.restart().asSeconds();
            square.updateWithMap(dt, plateform, enumVector);
            if (square.getLevelOver()) window.close();
            float xcamera=square.getPosition().x;
            float ycamera=square.getPosition().y;
            ScreenSize = window.getSize();
            float screen_w=ScreenSize.x/4;
            float screen_h=ScreenSize.y/4;
            xcamera=std::clamp(xcamera,screen_w/2+tile_width,map_width*tile_width-screen_w/2-tile_width);
            ycamera=std::clamp(ycamera,screen_h/2+tile_height,map_height*tile_height-screen_h/2-tile_height);
            gf::ExtendView camera({xcamera,ycamera}, {screen_w, screen_h});
            enumVector.clear();
            if (isresize)
            {
                isresize = false;
                gf::RenderWindow render(window);
            }
            // render
            render.clear(gf::Color::Black);
            render.setView(camera);
            // for (auto &plateform : plateform)
            // {
            //     plateform.second.render(render);
            // }
            std::string levelName = "level0" + std::to_string(level) + ".tmx";
            swiftness::LevelRender levelRender;
            levelRender.renderLevel(levelName, render,square.getGravity());
            square.render(render);
            square.renderHUD(render,screen_w,screen_h,{xcamera,ycamera});

            render.display();
        }
        level = -2;
    }   
    return 0;
}