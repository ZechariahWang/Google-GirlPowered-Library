#include "main.h"

GirlPowered::AssetConfig config(

	/**
	 * @brief Ports for the left side of the drivetrain. Enter the number the wire is connected to.
	 * If it spins the wrong way, add a negative sign in front of the number.
	 * 
	 */

	{20},   

	/**
	 * @brief Ports for the right side of the drivetrain. Enter the number the wire is connected to.
	 * If it spins the wrong way, add a negative sign in front of the number.
	 * 
	 */ 

	{-12},   

	/**
	 * @brief Port for the arm of the clawbot. Enter the number the wire is connected to.
	 * If it spins the wrong way, add a negative sign in front of the number.
	 * 
	 */     

	{-11},  

	/**
	 * @brief Ports for the claw of the clawbot. Enter the number the wire is connected to.
	 * If it spins the wrong way, add a negative sign in front of the number.
	 * 
	 */                  

	{-19}                    
); 

/**
 * @brief Speed of the arm for the robot. If the claw spins the wrong way, make the number negative
 * 
 */ 

const int8_t ARM_SPEED = 127;

/**
 * @brief Speed of the claw for the robot. If the claw spins the wrong way, make the number negative
 * 
 */ 

const int8_t CLAW_SPEED = 127;

/**
 * @brief Refresh time for the loop. Usually 10ms. Dont suggest changing this number
 * 
 */ 

const uint8_t REFRESH_TIME = 10;


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


void autonomous() {
	forward.move(48, 40);
	rotate.turn(90, 40);
	forward.move(24, 40);
	arm.move_arm(60, 1, GirlPowered::ArmController::direction::UP);
	arm.move_arm(60, 1, GirlPowered::ArmController::direction::DOWN);
	claw.move_claw(60, 1, GirlPowered::ClawController::direction::CLOSE);
	claw.move_claw(60, 1, GirlPowered::ClawController::direction::OPEN);
	forward.move(-20, 40);
	rotate.turn(-100, 40);
	forward.move(-48, 40);

}

void opcontrol() {
	while (true) {
		driver.drivetrain_controller();
		driver.arm_controller(ARM_SPEED);
		driver.claw_controller(CLAW_SPEED);
		pros::lcd::print(2, "heading: %f", rotate.current_robot_heading());
		pros::delay(REFRESH_TIME);
	}
}
