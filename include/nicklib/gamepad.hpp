#pragma once

#ifndef PROS_USE_SIMPLE_NAMES
#define PROS_USE_SIMPLE_NAMES
#endif

#include <array>
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
#include "Eigen/Core"


namespace nicklib {
class Button {
    public:
        Button(pros::controller_digital_e_t id);

        /**
         * Updates the state of the button.
         * @param newState Whether or not the button is currently pressed down.
         */
        void update(bool newState);

        /**
         * Gets the ID of the button.
         * @return The ID of the button.
         */
        [[nodiscard]] pros::controller_digital_e_t getID() const;

        /**
         * Converts the button to a boolean value.
         * @return true if the button is held, false otherwise.
         */
        explicit operator bool() const;

        /**
         * Converts the button to an integer value.
         * @return The time the button has been held for in milliseconds.
         */
        explicit operator int() const;

        bool isHeld = false, isPressed = false, isReleased = false;
    protected:
        pros::controller_digital_e_t id;
        std::uint32_t startTime = 0;
};

class Gamepad : public pros::Controller {
    public:
        explicit Gamepad(pros::controller_id_e_t id);

        /**
         * Updates the state of the gamepad (all joysticks and buttons).
         * @note This function should be called at the beginning of every loop iteration.
         * @note Create a separate instance for each task.
         */
        void update();

        // Face letter buttons
        Button x {pros::E_CONTROLLER_DIGITAL_X}, a {pros::E_CONTROLLER_DIGITAL_A}, b {pros::E_CONTROLLER_DIGITAL_B},
            y {pros::E_CONTROLLER_DIGITAL_Y};

        // D-pad buttons
        Button d_up {pros::E_CONTROLLER_DIGITAL_UP}, d_right {pros::E_CONTROLLER_DIGITAL_RIGHT},
            d_down {pros::E_CONTROLLER_DIGITAL_DOWN}, d_left {pros::E_CONTROLLER_DIGITAL_LEFT};

        // Bumpers and triggers
        Button l1 {pros::E_CONTROLLER_DIGITAL_L1}, l2 {pros::E_CONTROLLER_DIGITAL_L2},
            r1 {pros::E_CONTROLLER_DIGITAL_R1}, r2 {pros::E_CONTROLLER_DIGITAL_R2};

        // Joysticks
        Eigen::Vector2d leftStick, rightStick;
        double &leftX = leftStick[0], &leftY = leftStick[1], &rightX = rightStick[0], &rightY = rightStick[1];
    protected:
        // Pointer array for joysticks
        std::array<Eigen::Vector2d*, 4> ptrSticksArr = {&leftStick, &rightStick};

        // Pointer array for buttons
        std::array<Button*, 12> buttons {&x, &a, &b, &y, &d_up, &d_right, &d_down, &d_left, &l1, &l2, &r1, &r2};
};
} // namespace nicklib
