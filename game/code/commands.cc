#include "commands.h"

namespace swiftness {
    CommandsManager::CommandsManager() {}
    CommandsManager::~CommandsManager() {}

    void CommandsManager::manageCommands(std::vector<Input>& enumVector, const gf::Event& event) {
        switch (event.type) {
            case gf::EventType::Closed:
                enumVector.push_back(Input::Closed);
                break;            
            case gf::EventType::Resized:
                enumVector.push_back(Input::Resized);
                break;
            case gf::EventType::KeyPressed:
                switch (event.key.keycode) {
                    case gf::Keycode::Escape:
                        enumVector.push_back(Input::Escape);
                        break;
                    case gf::Keycode::B:
                        enumVector.push_back(Input::B);
                        break;
                    case gf::Keycode::Up:
                        enumVector.push_back(Input::Up);
                        break;
                    case gf::Keycode::Z:
                        enumVector.push_back(Input::Z);
                        break;
                    case gf::Keycode::Space:
                        enumVector.push_back(Input::Space);
                        break;
                    case gf::Keycode::Down:
                        enumVector.push_back(Input::Down);
                        break;
                    case gf::Keycode::S:
                        enumVector.push_back(Input::S);
                        break;
                    case gf::Keycode::Left:
                        enumVector.push_back(Input::Left);
                        break;
                    case gf::Keycode::Q:
                        enumVector.push_back(Input::Q);
                        break;
                    case gf::Keycode::Right:
                        enumVector.push_back(Input::Right);
                        break;
                    case gf::Keycode::D:
                        enumVector.push_back(Input::D);
                        break;
                    default:
                        break;
                }
                break;

            case gf::EventType::KeyReleased:
                switch (event.key.keycode) {
                    case gf::Keycode::Up:
                        enumVector.push_back(Input::UpReleased);
                        break;
                    case gf::Keycode::Z:
                        enumVector.push_back(Input::Z_Released);
                        break;
                    case gf::Keycode::Space:
                        enumVector.push_back(Input::Space_Released);
                        break;
                    case gf::Keycode::Down:
                        enumVector.push_back(Input::DownReleased);
                        break;
                    case gf::Keycode::S:
                        enumVector.push_back(Input::S_Released);
                        break;
                    case gf::Keycode::Left:
                        enumVector.push_back(Input::LeftReleased);
                        break;
                    case gf::Keycode::Q:
                        enumVector.push_back(Input::Q_Released);
                        break;
                    case gf::Keycode::Right:
                        enumVector.push_back(Input::RightReleased);
                        break;
                    case gf::Keycode::D:
                        enumVector.push_back(Input::D_Released);
                        break;
                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }
}