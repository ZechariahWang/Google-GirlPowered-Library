/**
 * @file RotationPID.cpp
 * @author Zechariah Wang
 * @brief Controls turning for the robot during the autonomous phase
 * @brief You do not need to edit these functions
 * 
 */

#include "main.h"

using namespace GirlPowered;

GirlPowered::RotationPID::RotationPID() {
    rotate.r_kp = 5;
    rotate.r_ki = 0;
    rotate.r_kd = 45;
}

void GirlPowered::RotationPID::set_rotation_pid_constants(double p, double i, double d) {
    rotate.r_kp = p;
    rotate.r_ki = i;
    rotate.r_kd = d;
}
                 
void GirlPowered::RotationPID::reset_rotation_values() {
    rotate.r_derivative = 0;
    rotate.r_integral = 0;
    rotate.r_error = 0;
    rotate.r_prev_error = 0;
    rotate.r_iterator = 0;
    rotate.r_failsafe = 0;
}

double get_min_angle_error_pid(float angle1, float angle2, bool radians){
    float max = radians ? 2 * M_PI : 360;
    float half = radians ? M_PI : 180;
    angle1 = fmod(angle1, max);
    angle2 = fmod(angle2, max);
    float error = angle1 - angle2;
    if (error > half) error -= max;
    else if (error < -half) error += max;
    return error;
}

double previousLeft = 0;
double previousRight = 0;
double previousHeading;
double totalAngle;
double GirlPowered::RotationPID::current_robot_heading() {
    double currentLeft = chassis_left_motors.at(0).get_position() * 2.75 * (M_PI / 360);
    double currentRight = chassis_right_motors.at(0).get_position() * 2.75 * (M_PI / 360);
    double deltaLeft = currentLeft - previousLeft;
    double deltaRight = currentRight - previousRight;
    double distanceLeft = 10;
    double distanceRight = 10;
    double heading = (deltaLeft - deltaRight) / (distanceLeft + distanceRight);
    heading = heading * (180 / M_PI);
    double deltaAngle;
    totalAngle += heading;
    deltaAngle = heading - previousHeading;
    previousLeft = currentLeft;
    previousRight = currentRight;
    previousHeading = heading;
    double globalTheta;
    double p = (heading - deltaAngle / 2.0) * (180 / M_PI); 
    globalTheta = fmod(totalAngle, 360);
    while (globalTheta < 0) {
        globalTheta += 360;
    }
    while (globalTheta > 360) {
        globalTheta -= 360;
    }
    return globalTheta;
}

double GirlPowered::RotationPID::compute_rotation_pid(double current, double target) {
  rotate.r_error = get_min_angle_error_pid(target, current_robot_heading(), false);
  rotate.r_derivative = rotate.r_error - rotate.r_prev_error;
  if (rotate.r_ki != 0){ rotate.r_integral += rotate.r_error; }
  if (rotate.r_error == 0 || rotate.r_error > target){ rotate.r_integral = 0; }

  double output = (rotate.r_kp * rotate.r_error) + (rotate.r_integral * rotate.r_ki) + (rotate.r_derivative * rotate.r_kd);
  if (output * (12000.0 / 127) >= rotate.r_max_speed * (12000.0 / 127)) { output = rotate.r_max_speed; }
  if (output * (12000.0 / 127) <= -rotate.r_max_speed * (12000.0 / 127)) { output = -rotate.r_max_speed; }
  rotate.r_prev_error = rotate.r_error;
  return output;
}

void GirlPowered::RotationPID::turn(double target, double speed) {
  chassis_left_motors.at(0).set_zero_position(0);
  chassis_right_motors.at(0).set_zero_position(0);
  rotate.reset_rotation_values();
  rotate.r_max_speed = speed;
  double local_timer = 0;
  while (true){
    double currentPos = current_robot_heading();
    double vol = rotate.compute_rotation_pid(currentPos, target);

    util.move_left_motors(vol * (12000.0 / 127));
    util.move_right_motors(-vol * (12000.0 / 127));
    if (fabs(rotate.r_error) < 3) { rotate.r_iterator++; } else { rotate.r_iterator = 0;}
    if (fabs(rotate.r_iterator) >= 3){
      util.move_left_motors(0);
      util.move_right_motors(0);
      break;
    }
    if (fabs(rotate.r_error - rotate.r_prev_error) < 0.001) {rotate.r_failsafe++;}
    if (rotate.r_failsafe > 100){
      util.move_left_motors(0);
      util.move_right_motors(0);
      break;
    }
    pros::delay(10);
  }
}