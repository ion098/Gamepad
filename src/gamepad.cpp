#include "main.h"

Gamepad::Gamepad(pros::controller_id_e_t id) {
    controllerID = id;
}

double Gamepad::curveStickInput(double rawInput) {
    int sign = (rawInput > 0) ? 1 : ((rawInput < 0) ? -1 : 0);
    if (rawInput == 0) return 0;
    else if (fabs(rawInput) <= 0.9) return (sign*(pow(rawInput, 2)+0.1));
    else if (fabs(rawInput) <= 1) return sign;
    else return 0;
}

void Gamepad::getInputs() {
    pros::Controller controller(controllerID);

    // Guard clause against a disabled controller (during auton and semi-autons)
    // Use the B button to cancel semi autons
    if (disabled) {
        b.setStatus(controller.get_digital(DIGITAL_B));
        return;
    }
    
    // Get the input value for the stick axes
    for (int i = 0; i < 4; i++) {
        pros::controller_analog_e_t stick = static_cast<pros::controller_analog_e_t>(i);
        double rawStickInput = controller.get_analog(stick)/127.0;
        
        // Cross deadzone
        if (fabs(rawStickInput) <= CONTROLLER_DEADZONE) rawStickInput = 0;

        *ptrSticksArr[i] = curveStickInput(rawStickInput);
    }

    // Get the status for the buttons
    for (int i = 0; i < 12; i++) {
        /** NOTE: add 6 to i to match the pros::controller_digital_e_t enum in misc.h */
        pros::controller_digital_e_t button = static_cast<pros::controller_digital_e_t>(i+6);
        (*ptrButtonsArr[i]).setStatus(controller.get_digital(button));
    }
}

std::array<double, 2> Gamepad::processSticks() {
    pros::Controller controller(controllerID);

    double forwardsVel, turnVel;

    forwardsVel = controller.leftY;
    turnVel = controller.rightX*TURN_CONST;

    return {forwardsVel, turnVel};
}

void Gamepad::disable() {
    pros::Controller controller(controllerID);

    disabled = true;

    for (int i = 0; i < 4; i++) {
        pros::controller_analog_e_t stick = static_cast<pros::controller_analog_e_t>(i);
        *ptrSticksArr[i] = 0;
    }

    for (int i = 0; i < 12; i++) {
        /** NOTE: add 6 to i to match the pros::controller_digital_e_t enum in misc.h */
        pros::controller_digital_e_t button = static_cast<pros::controller_digital_e_t>(i+6);
        (*ptrButtonsArr[i]).disable();
    }
}

void Gamepad::resume() {
    disabled = false;
}