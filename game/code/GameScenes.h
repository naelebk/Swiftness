#include <gf/Scene.h>
#include <gf/Action.h>
#include <gf/Time.h>
#include <gf/Font.h>
#include <gf/Texture.h>
#include <gf/Widgets.h>
#include <gf/Clock.h>
#include <gf/Views.h>
#include <gf/View.h>
#include <gf/Color.h>
#include <gf/Event.h>
#include <gf/RenderTarget.h>
#include <gf/SegueEffect.h>
#include <gf/Shapes.h>
#include <gf/Vector.h>
#include <gf/Window.h>
#include <gf/Math.h>

// Concernant la création et la gestion des scènes, tout ce qui concerne également les différents rendus,
// nous nous sommes largement inspiré d'un lien Github qui nous a été fourni, concernant un jeu créé lors
// d'une global game jam (2022 ici)
// lien source : https://github.com/Hatunruna/ggj2022/tree/main/code/bits

namespace swiftness {
    class GameManager : public gf::Scene {
        public:
            //const static gf::Font font("../../ressources/font/ActiveSpaceDemoRegular.ttf");
            // Constructeur
            GameManager();
            // Destructeur
            ~GameManager();

            // On aura plusieurs render dans notre main, cette fonction nous permettra de tout rendre directement
            // Ça sera bien plus simple dans la gestion des rendus du jeu
            void renderEverything(gf::RenderTarget& targets...);

            // Cette fonction permet de créer une nouvelle scène à partir
            void createNewScene(gf::Scene& scene, gf::Window& window);
            
            // Cette fonction va nous permettre de faire une transition entre deux scènes du jeu
            void transition(gf::SegueEffect segue);

            // Cette fonction permet de gérer un évènement dans notre scène
            void manageEvents(gf::Event& event);

            // Cette fonction permet de gérer les actions de part la fenêtre choisie
            void manageWindowEvents(gf::Window& window);

            

        private:
            // Tous ces attributs vont nous servir à gérer de manière correcte les scènes, à savoir : 
            /*
                - les boutons
                - les actions concernant ces boutons (le crédit, jouer une partie, quitter le jeu)
            */
            gf::Scene scene;
            gf::Action action;
            gf::SegueEffect effect;
            //gf::Texture& background;
            gf::Action quit_a;
            gf::Action up;
            gf::Action questionmark;
            gf::Action down;
            gf::Action trigger;
            gf::TextButtonWidget quit_b;
            gf::TextButtonWidget credits;
            gf::TextButtonWidget choose_level;
            gf::TextButtonWidget questionmark_b;
    };
}