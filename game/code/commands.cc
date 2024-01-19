#include "commands.h"

namespace swiftness {
    CommandsManager::CommandsManager() : 
    up("Up"), 
    down("Down"), 
    left("Left"), 
    right("Right"),
    gamepad() {
        gf::Gamepad::initialize();
        up.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Negative);
        down.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Positive);
        left.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Negative);
        right.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Positive);
    }
    CommandsManager::~CommandsManager() {
    }

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
            case gf::EventType::GamepadAxisMoved:
                switch (event.gamepadAxis.axis) {
                    case gf::GamepadAxis::LeftY:
                        if (down.isActive()) {
                            down.processEvent(event);
                            enumVector.push_back(Input::Down);
                        } else {
                            down.processEvent(event);
                            enumVector.push_back(Input::DownReleased);
                        }
                        if (up.isActive()) {
                            up.processEvent(event);
                            enumVector.push_back(Input::Up);
                        } else {
                            up.processEvent(event);
                            enumVector.push_back(Input::UpReleased);
                        }
                        break;
                    case gf::GamepadAxis::LeftX:
                        if (right.isActive()) {
                            right.processEvent(event);
                            enumVector.push_back(Input::Right);
                        } else {
                            right.processEvent(event);
                            enumVector.push_back(Input::RightReleased);
                        }
                        if (left.isActive()) {
                            left.processEvent(event);
                            enumVector.push_back(Input::Left);
                        } else {
                            left.processEvent(event);
                            enumVector.push_back(Input::LeftReleased);
                        }
                        break;
                    default:
                        break;
                }
                break;
            case gf::EventType::GamepadButtonPressed:
                switch(event.gamepadButton.button) {
                    // Pour sauter : deux manières différentes => haut ou A
                    case gf::GamepadButton::A:
                        enumVector.push_back(Input::Space);
                        break;
                    case gf::GamepadButton::B:
                        enumVector.push_back(Input::Closed);
                        break;
                    case gf::GamepadButton::DPadUp:
                        enumVector.push_back(Input::Up);
                        break;
                    case gf::GamepadButton::DPadLeft:
                        enumVector.push_back(Input::Left);
                        break;
                    case gf::GamepadButton::DPadRight:
                        enumVector.push_back(Input::Right);
                        break;
                    case gf::GamepadButton::DPadDown:
                        enumVector.push_back(Input::Down);
                        break;
                    default:
                        break;                    
                }
                break;
            case gf::EventType::GamepadButtonReleased:
                switch(event.gamepadButton.button) {
                    case gf::GamepadButton::A:
                        enumVector.push_back(Input::Space_Released);
                        break;
                    case gf::GamepadButton::B:
                        enumVector.push_back(Input::Closed);
                        break;
                    case gf::GamepadButton::DPadUp:
                        enumVector.push_back(Input::UpReleased);
                        break;
                    case gf::GamepadButton::DPadLeft:
                        enumVector.push_back(Input::LeftReleased);
                        break;
                    case gf::GamepadButton::DPadRight:
                        enumVector.push_back(Input::RightReleased);
                        break;
                    case gf::GamepadButton::DPadDown:
                        enumVector.push_back(Input::DownReleased);
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
    }
}