#include "nicklib/util.hpp"

/**
 * @brief Curves the input.
 * @param input the number to curve.
 * @param gain gain value of the curve.
 * @param scale the max value of the input/output.
 * @return the curved input.
 */
float nicklib::curveInput(float input, float gain, float scale) {
    input /= scale;
    if (input <= 0) {
        input = -1 * (1 - powf(M_E, -1 * gain * input)) / (1 - powf(M_E, gain));
    } else {
        input = (1 - powf(M_E, gain * input)) / (1 - powf(M_E, gain));
    }
    return input * scale;
}

/**
 * @brief Normalizes the velocities.
 * @param vel1 the first velocity.
 * @param vel2 the second velocity.
 * @param scale the max value of the input/output.
 * @return array of the normalized velocities.
 */
std::array<float, 2> nicklib::normalizeVels(float vel1, float vel2, float scale) {
    float highVel = std::max(std::fabs(vel1), std::fabs(vel1));
    if (std::fabs(highVel) > scale) {
        vel1 /= highVel;
        vel2 /= highVel;
    }
    return {vel1, vel2};
}

/**
 * @brief Normalizes the velocities.
 * @param vels vector of velocities.
 * @param scale the max value of the input/output.
 * @return vector of the normalized velocities.
 */
std::vector<float> nicklib::normalizeVels(std::vector<float> vels, float scale) {
    float highVel = 0;
    for (float vel : vels) {
        if (std::fabs(vel) > highVel) {
            highVel = std::fabs(vel);
        }
    };

    if (std::fabs(highVel) > scale) {
        for (float &vel : vels) {
            vel /= highVel;
        }
    }
    return vels;
}

/**
 * @brief Applies a cross deadzone to the input.
 * @param input the input to apply the deadzone to.
 * @param deadzone the minimum input to consider.
 * @return the input with the deadzone applied.
 */
float nicklib::deadzone(float input, float deadzone) {
    if (std::fabs(input) < deadzone) {
        return 0;
    }
    return input;
}