#include "nicklib/gamepad.hpp"

namespace Nicklib {
void Gamepad::updateButton(ButtonState Gamepad::* button, bool is_held) {
    this->*button.rising_edge = !this->*button.is_pressed && is_held;
    this->*button.falling_edge = this->*button.is_pressed && !is_held;
    this->*button.is_pressed = is_held;
    if (is_held) {
        this->*button.last_press_time = pros::millis();
    } else {
        this->*button.last_release_time = pros::millis();
    }
}

void Gamepad::update() {
    this->updateButton(&Gamepad::L1);
    this->updateButton(&Gamepad::L2);
    this->updateButton(&Gamepad::R1);
    this->updateButton(&Gamepad::R2);
    this->updateButton(&Gamepad::Up);
    this->updateButton(&Gamepad::Down);
    this->updateButton(&Gamepad::Left);
    this->updateButton(&Gamepad::Right);
    this->updateButton(&Gamepad::X);
    this->updateButton(&Gamepad::B);
    this->updateButton(&Gamepad::Y);
    this->updateButton(&Gamepad::A);

    this->LeftX = this->controller.get_analog(ANALOG_LEFT_X);
    this->LeftY = this->controller.get_analog(ANALOG_LEFT_Y);
    this->RightX = this->controller.get_analog(ANALOG_RIGHT_X);
    this->RightY = this->controller.get_analog(ANALOG_RIGHT_Y);
}

void Gamepad::operator[](pros::controller_digital_e_t button) {
    // TODO: fill in switch
    switch (button) {
        default: std::exit(1); 
    }
}
}