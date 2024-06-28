
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

