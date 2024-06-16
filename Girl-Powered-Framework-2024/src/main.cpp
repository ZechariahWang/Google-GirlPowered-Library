#include "main.h"

GirlPowered::AssetConfig config(

	/**
	 * @brief Ports for the left side of the drivetrain. Enter the number the wire is connected to.
	 * If it spins the wrong way, add a negative sign in front of the number.
	 * 
	 */

	{-16, -21, -17, -1},   

	/**
	 * @brief Ports for the right side of the drivetrain. Enter the number the wire is connected to.
	 * If it spins the wrong way, add a negative sign in front of the number.
	 * 
	 */ 

	{19, 20, 18, 7},   

	/**
	 * @brief Port for the arm of the clawbot. Enter the number the wire is connected to.
	 * If it spins the wrong way, add a negative sign in front of the number.
	 * 
	 */     

	{2},  

	/**
	 * @brief Ports for the claw of the clawbot. Enter the number the wire is connected to.
	 * If it spins the wrong way, add a negative sign in front of the number.
	 * 
	 */                  

	{4}                    
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


void initialize() { pros::lcd::initialize(); pros::lcd::set_text(1, "Welcome to Girl Powered 2024!"); }
void disabled() {}
void competition_initialize() {}


void autonomous() {}

void opcontrol() {
	while (true) {
		driver.drivetrain_controller();
		driver.arm_controller(ARM_SPEED);
		driver.claw_controller(CLAW_SPEED);
		pros::delay(REFRESH_TIME);
	}
}
