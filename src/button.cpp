#include "main.h"

Button::Button() {}

void Button::setStatus(bool isPressed) {
    currState = isPressed;
    
    // Rising edge detection
    if (!prevState && currState) {
        pressed = true;
        held = true;
        released = false;
    }
    
    // Sustained
    else if (prevState && currState) {
        pressed = false;
        held = true;
        released = false;
    }
    
    // Falling edge detection
    else if (prevState && !currState) {
        pressed = false;
        held = false;
        released = true;
    }
    
    // Not pressed
    else {
        pressed = false;
        held = false;
        released = false;
    }

    // Update for next iteration
    prevState = currState;
}

void Button::disable() {
    pressed = false;
    held = false;
    released = false;
}

Button::operator bool() const {
    return held;
}

