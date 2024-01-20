#pragma once
#include "main.h"

class Gamepad {
    private:
        pros::controller_id_e_t controllerID;

        // Pointer array for joysticks
        std::array<double*, 4> ptrSticksArr = {
            &leftX, &leftY, &rightX, &rightY
        };

        // Pointer array for buttons (using wrapper button class)
        std::array<Button*, 12> ptrButtonsArr = {
            &lb, &lt, &rb, &rt,
            &dpadUp, &dpadDown, &dpadLeft, &dpadRight,
            &x, &b, &y, &a
        };

    public:
        double leftX, leftY, rightX, rightY;
        Button lb, lt, rb, rt;
        Button dpadUp, dpadDown, dpadLeft, dpadRight;
        Button x, b, y, a;

        bool disabled;

        /** Gamepad class constructor
         * \param id
         *        MASTER or PARTNER
         */
        Gamepad(pros::controller_id_e_t id);

        /**
         * Processes the inputs from the gamepad sticks to curve them
         * \param rawInput (uncurved double from [-1,1])
         * \return curved output from [-1, 1]
         */
        double curveStickInput(double rawInput);

        /** 
         * Gets the inputs from the gamepad
         * \param None
         * \note Should run in task
         */
        void getInputs();
        
        /**
         * Processes the inputs from the gamepad sticks and converts them to movement powers. 
         * \param None
         * \return Lateral power and turning power (std::array<double, 2>)
         */
        std::array<double, 2> processSticks();

        /** 
         * Sets all gamepad inputs to 0 or false (except cancel button)
         * \param None
         * \note Used when running semi auton
         */
        void disable();

        /** 
         * Sets disabled to false
         * \param None
         * \note Used every time we cancel or end auton/semiauton
         */
        void resume();
};
