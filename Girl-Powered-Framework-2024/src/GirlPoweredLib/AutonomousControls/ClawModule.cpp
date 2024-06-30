/**
 * @file ClawModule.cpp
 * @author Zechariah Wang
 * @brief Controls the claw of the robot during the autonomous phase.
 * @brief You do not need to edit these functions.
 * 
 */

#include "main.h"

using namespace GirlPowered;

void ClawController::move_claw(double speed, double time, direction dir) {
    switch (dir) {
        case direction::OPEN:
            std::cout << "Opening claw." << std::endl;
            util.move_claw_motors(-speed * (12000.0 / 127));
            pros::delay(time * 1000);
            util.move_claw_motors(0);
            break;
        case direction::CLOSE:
            std::cout << "Closing claw." << std::endl;
            util.move_claw_motors(speed * (12000.0 / 127));
            pros::delay(time * 1000);
            util.move_claw_motors(0);
            break;
        default:
            std::cout << "Unknown direction." << std::endl;
            break;
    }
}