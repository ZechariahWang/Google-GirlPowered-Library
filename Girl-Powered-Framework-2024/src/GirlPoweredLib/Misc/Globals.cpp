/**
 * @file Globals.cpp
 * @author Zechariah Wang
 * @brief This is the code that declares the subsystems the rest of the robot will use.
 * @brief You do not need to edit these functions
 * 
 */

#include "pros/adi.hpp"
#include "main.h"
#include "pros/misc.h"

using namespace GirlPowered;

pros::Controller controller(pros::E_CONTROLLER_MASTER);

Utility util;
DriverController driver;
MovementPID forward;
RotationPID rotate;
ArmController arm;
ClawController claw;

