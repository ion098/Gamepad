#include "nicklib/util.hpp"
#include <cmath>

float nicklib::curveInput(float input, float gain, float scale) {
    input /= scale;
    if (input <= 0) {
        input = -1 * (1 - powf(M_E, -1 * gain * input)) / (1 - powf(M_E, gain));
    } else {
        input = (1 - powf(M_E, gain * input)) / (1 - powf(M_E, gain));
    }
    return input * scale;
}

std::array<float, 2> nicklib::normalizeVels(float vel1, float vel2, float scale) {
    float highVel = std::max(std::fabs(vel1), std::fabs(vel1));
    if (std::fabs(highVel) > scale) {
        vel1 /= highVel;
        vel2 /= highVel;
    }
    return {vel1, vel2};
}

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

float nicklib::deadzone(float input, float deadzone) {
    if (std::fabs(input) < deadzone) {
        return 0;
    }
    return input;
}