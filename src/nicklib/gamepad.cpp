#include "nicklib/gamepad.hpp"

nicklib::Button::Button(pros::controller_digital_e_t id)
    : id(id) {}

void nicklib::Button::update(bool newState) {
    this->isPressed = !this->isHeld && newState;
    this->isReleased = this->isHeld && !newState;
    this->isHeld = newState;

    if (this->isPressed) { this->startTime = pros::millis(); }
}

nicklib::Button::operator bool() const { return this->isHeld; }

nicklib::Button::operator int() const {
    if (this->isHeld) return pros::millis() - this->startTime;
    else return 0;
}

pros::controller_digital_e_t nicklib::Button::getID() const { return this->id; }

nicklib::Gamepad::Gamepad(pros::controller_id_e_t id)
    : pros::Controller(id) {}

void nicklib::Gamepad::update() {
    for (Button* button : this->buttons) { button->update(this->get_digital(button->getID())); }
    leftStick = {this->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X),
                 this->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)};
    rightStick = {this->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X),
                  this->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)};
}