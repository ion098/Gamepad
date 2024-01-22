#include "nicklib/button.hpp"

nicklib::Button::Button() {}

void nicklib::Button::setStatus(bool isPressed) {
    currState = isPressed;

    // Rising edge detection
    if (!prevState && currState) {
        pressed = true;
        held = true;
        released = false;
        startTime = pros::millis();
        heldTime = 0;
    }

    // Sustained
    else if (prevState && currState) {
        pressed = false;
        held = true;
        released = false;
        currTime = pros::millis();
        heldTime = currTime - startTime;
    }

    // Falling edge detection
    else if (prevState && !currState) {
        pressed = false;
        held = false;
        released = true;
        startTime = -1;
        heldTime = -1;
    }

    // Not pressed
    else {
        pressed = false;
        held = false;
        released = false;
        startTime = -1;
        heldTime = -1;
    }

    // Update for next iteration
    prevState = currState;
}

nicklib::Button::operator bool() const { return held; }

nicklib::Button::operator int() const { return heldTime; }
