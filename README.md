# NickLib
 
A simple gamepad template for PROS (for VEX Robotics Competition)

## Tutorial
To construct a new gamepad, use `nicklib::gamepad Gamepad(pros::E_CONTROLLER_MASTER)`

Put `gamepad.update()` in the loop for opcontrol.

The stick axes are `leftX`, `leftY`, `rightX`, and `rightY` with an output range of [-1, 1] (so multiply by 127 when passing into pros motors).

Buttons are `x`, `y`, `a`, `b`, `dpadUp`, `dpadLeft`, `dpadRight`, `dpadDown`, `lb`, `lt`, `rb`, and `rt`.

Example calls
```cpp
gamepad.x // true if the x button is held down
(int)gamepad.a // how long the a button has been held down in milliseconds
gamepad.lt.pressed // returns a new press for left trigger
gamepad.dpadUp.released // returns a new release for dpad up

gamepad.leftY // returns the position of the left stick y axis
```
