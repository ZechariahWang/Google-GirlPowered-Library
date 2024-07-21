/**
 * @file AutonScript.cpp
 * @author Zechariah Wang
 * @brief Reference functions to help you understand how to use the autonomous functions
 * 
 */

#include "main.h"


/**
 * @brief Move the robot forwards and backwards 48 inches
 * 
 */

void MoveForwardsAndBackwards() {
    forward.move(24, 40); // First number is the distance in inches, second number is the speed from 0 to 127.
    forward.move(-24, 40); // First number is the distance in inches, second number is the speed from 0 to 127.
}

/**
 * @brief Turn 90 degrees right and turn back to original direction
 * 
 */

void Turn90DegreesAndBack() {
    rotate.turn(90, 40); // First number is the amount in degrees, second number is the speed from 0 to 127.
	rotate.turn(-90, 40); // First number is the amount in degrees, second number is the speed from 0 to 127.
}

/**
 * @brief Open claw and then close it again
 * 
 */

void OpenAndCloseClaw() {
	claw.move_claw(60, 1, GirlPowered::ClawController::direction::OPEN); // First number is the speed, second number is the amount of time in seconds, third value is the direction that it moves.
	claw.move_claw(60, 1, GirlPowered::ClawController::direction::CLOSE); // First number is the speed, second number is the amount of time in seconds, third value is the direction that it moves.
}

/**
 * @brief Moves arm up and then moves it back down again
 * 
 */

void MoveArmUpAndDown() {
	arm.move_arm(60, 1, GirlPowered::ArmController::direction::UP); // First number is the speed, second number is the amount of time in seconds, third value is the direction that it moves.
	arm.move_arm(60, 1, GirlPowered::ArmController::direction::DOWN); // First number is the speed, second number is the amount of time in seconds, third value is the direction that it moves.
}