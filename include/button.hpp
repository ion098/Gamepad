#pragma once
#include "main.h"

class Button {
    private:
        bool prevState = false, currState = false;

    public:
        // Button statuses
        bool pressed, released, held;
        
        /**
         * Button class constructor
         * \param None
         * \note Should only be used by gamepad class and not in loose code
         */
        Button();

        /** 
         * Sets the button state of pressed, held, and released
         * \param isPressed
         *        from gamepad.get_digital()
         * \returns `None`
         * \note Should only be used in gamepad class, not for general code.
         */
        void setStatus(bool isPressed);

        /**
         * Sets the button states to false
         * \param None
         * \returns `None`
         * \note Should only be used by gamepad class, not for general code.
         *       To be used when running semi autons when gamepad is disabled.
         */
        void disable();

        /**
         * Casts button to boolean.
         * Returns true if the button is held, false otherwise.
         * \note Equivalent to `{gamepad}.{button}.held`
         */
        explicit operator bool() const;
};