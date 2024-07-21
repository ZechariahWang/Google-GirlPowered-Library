/**
 * @file main.cpp
 * @brief The main driver code for the rest of the robot!
 * 
 */

#include "main.h"
#include "GirlPoweredLib/Scripts/AutonScript.hpp"

GirlPowered::AssetConfig config(

	/**
	 * @brief Ports for the left side of the clawbot. Enter the number the wire is connected to.
	 * If it spins the wrong way, add a negative sign in front of the number.
	 * 
	 */

	{17},   

	/**
	 * @brief Ports for the right side of the clawbot. Enter the number the wire is connected to.
	 * If it spins the wrong way, add a negative sign in front of the number.
	 * 
	 */ 

	{-11},   

	/**
	 * @brief Port for the arm of the clawbot. Enter the number the wire is connected to.
	 * If it spins the wrong way, add a negative sign in front of the number.
	 * 
	 */     

	{-1},  

	/**
	 * @brief Ports for the claw of the clawbot. Enter the number the wire is connected to.
	 * If it spins the wrong way, add a negative sign in front of the number.
	 * 
	 */                  

	{-19}                    
); 

/**
 * @brief Speed of the arm for the robot. If the claw spins the wrong way, make the number negative.
 * 
 */ 

const int8_t ARM_SPEED = 127;

/**
 * @brief Speed of the claw for the robot. If the claw spins the wrong way, make the number negative.
 * 
 */ 

const int8_t CLAW_SPEED = 127;

/**
 * @brief Refresh time for the loop. Usually 10ms. Dont need to change this number.
 * 
 */ 

const uint8_t REFRESH_TIME = 10;

/**
 * @brief This function controls initialize parameters. You do not need to edit this function.
 * 
 */ 

void initialize() { 
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Welcome to Girl Powered 2024!");
	forward.set_movement_pid_constants(5, 0, 35);
	rotate.set_rotation_pid_constants(5, 0, 45);
	claw_motors.at(0).set_zero_position(0);
	arm_motors.at(0).set_zero_position(0);
	claw_motors.at(0).set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	arm_motors.at(0).set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void disabled() {}	
void competition_initialize() {}

/**
 * @brief FUNCTION REFERENCES. IF YOU ARE STILL CONFUSED ON HOW THESE WORK, GO INTO THE SCRIPTS FOLDER AND CLICK ON AutonScripts.cpp 
 * forward.move(AMOUNT IN INCHES, SPEED FROM 0 TO 127);
 * rotate.turn(AMOUNT IN DEGREES, SPEED FROM 0 TO 127);
 * arm.move_arm(SPEED FROM 0 TO 127, TIME IN SECONDS, DIRECTION OF ARM (SEE ENUM LIST BELOW));
 * claw.move_claw(SPEED FROM 0 TO 127, TIME IN SECONDS, DIRECTION OF CLAW (SEE ENUM LIST BELOW));
 */ 

/**
 * @brief ENUM LIST FOR DIRECTION OF ARM AND CLAW
 * GirlPowered::ArmController::direction::UP
 * GirlPowered::ArmController::direction::DOWN
 * GirlPowered::ClawController::direction::OPEN
 * GirlPowered::ClawController::direction::CLOSE
 */ 

/**
 * @brief Paste your autonomous code into here!
 * @brief If you don't know what to put here, check out the scripts folder on the left for reference commands.
 */ 

void autonomous() {
	forward.move(24, 40);
	rotate.turn(-90, 40);
	claw.move_claw(60, 1, GirlPowered::ClawController::direction::OPEN); 
	claw.move_claw(60, 1, GirlPowered::ClawController::direction::CLOSE); 
	arm.move_arm(60, 1, GirlPowered::ArmController::direction::UP);
	arm.move_arm(60, 1, GirlPowered::ArmController::direction::DOWN);
}

/**
 * @brief This is the code that controls your driver input
 * @brief You dont't need to edit these functions
 */ 

void opcontrol() {
	while (true) {
		driver.drivetrain_controller();
		driver.arm_controller(ARM_SPEED);
		driver.claw_controller(CLAW_SPEED);
		pros::delay(REFRESH_TIME);
	}
}
