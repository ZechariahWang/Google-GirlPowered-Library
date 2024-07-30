/**
 * @file ArmModule.cpp
 * @author Zechariah Wang
 * @brief Controls the arm of the robot during the autonomous phase.
 * @brief You do not need to edit these functions.
 * 
 */

#include "main.h"

using namespace GirlPowered;

void ArmController::move_arm(double speed, double time, direction dir) {
    switch (dir) {
        case direction::UP:
            std::cout << "Moving arm up." << std::endl;
            util.move_arm_motors(-speed * (12000.0 / 127));
            pros::delay(time * 1000);
            util.move_arm_motors(0);
            arm_motors.at(0).brake();
            break;
        case direction::DOWN:
            std::cout << "Moving arm down" << std::endl;
            util.move_arm_motors(speed * (12000.0 / 127));
            pros::delay(time * 1000);
            util.move_arm_motors(0);
            arm_motors.at(0).brake();
            break;
        default:
            std::cout << "Unknown direction." << std::endl;
            break;
    }
}