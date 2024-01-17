#pragma once
#include <gf/Event.h>
#include <gf/Gamepad.h>
#include <vector>
#include "Input.h"

namespace swiftness {
    class CommandsManager {
        public:
            // Constructeur
            CommandsManager();
            // Destructeur
            ~CommandsManager();

            /**
            * Fonction permettant de gérer les commandes du jeu à travers cette méthode
            * @param enumVector : liste de commandes (touches) pressées par l'utilisateur
            * @param event : l'évènement associé à un gf::Event
            * @return : rien, car void
            */
            void manageCommands(std::vector<Input>& enumVector, const gf::Event& event);
        private:
            // Attribut privé nous permettant de gérer correctement le gamepad
            gf::GamepadTracker gamepad;
    };

}