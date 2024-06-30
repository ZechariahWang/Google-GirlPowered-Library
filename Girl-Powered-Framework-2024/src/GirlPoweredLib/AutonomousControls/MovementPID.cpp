/**
 * @file MovementPID.cpp
 * @author Zechariah Wang
 * @brief Controls moving forward and backward for the robot during the autonomous phase
 * @brief You do not need to edit these functions
 * 
 */

#include "main.h"

using namespace GirlPowered;

GirlPowered::MovementPID::MovementPID() {
    forward.m_kp = 5;
    forward.m_ki = 0;
    forward.m_kd = 35;
}

void GirlPowered::MovementPID::set_movement_pid_constants(double p, double i, double d) {
    forward.m_kp = p;
    forward.m_ki = i;
    forward.m_kd = d;
}

void GirlPowered::MovementPID::reset_movement_values() {
    forward.m_derivative = 0;
    forward.m_integral = 0;
    forward.m_error = 0;
    forward.m_prev_error = 0;
    forward.m_iterator = 0;
    forward.m_failsafe = 0;
}

double GirlPowered::MovementPID::compute_movement_pid(double current, double target) {
    forward.m_error = target - current;
    forward.m_derivative = forward.m_error - forward.m_prev_error;
    if (forward.m_ki != 0){
        forward.m_integral += forward.m_error;
    }
    if (util.sgn(forward.m_error) !=  util.sgn(forward.m_prev_error)){
        forward.m_integral = 0;
    }

    double output = (forward.m_kp * forward.m_error) + (forward.m_integral * forward.m_ki) + (forward.m_derivative * forward.m_kd);
    if (output * (12000.0 / 127) > forward.m_max_speed * (12000.0 / 127)) output = forward.m_max_speed;
    if (output * (12000.0 / 127) < -forward.m_max_speed * (12000.0 / 127)) output = -forward.m_max_speed;
    forward.m_prev_error = forward.m_error;
    return output;
}

double find_min_angle(int16_t targetHeading, int16_t currentrobotHeading){
  double turnAngle = targetHeading - currentrobotHeading;
  if (turnAngle > 180 || turnAngle < -180) { turnAngle = turnAngle - (util.sgn(turnAngle) * 360); }
  return turnAngle;
}

void GirlPowered::MovementPID::move(double target, double speed) {
  chassis_left_motors.at(0).set_zero_position(0);
  chassis_right_motors.at(0).set_zero_position(0);
  forward.reset_movement_values();
  double POSITION_TARGET = target; bool is_backwards = false; int8_t cd = 0;
  forward.m_max_speed = speed;
  double local_timer = 0;
  target *= 68;
  double TARGET_THETA = rotate.current_robot_heading();
  while (true){
    double avgPos = util.get_encoder_position();
    double avg_voltage_req = forward.compute_movement_pid(avgPos, target); // compute proportional integral derivative controller on filtered pos
    cd++; if (cd <= 2){ util.move_left_motors(0); util.move_right_motors(0); continue;} // initial timer to keep robot from oscillating
    if (target < 0) { is_backwards = true; } else { is_backwards = false; }
    double l_output = 0; double r_output = 0;
    l_output = avg_voltage_req;
    r_output = avg_voltage_req;

    double headingAssist = find_min_angle(TARGET_THETA, rotate.current_robot_heading()) * 500;
    util.move_left_motors(l_output * (12000.0 / 127) + headingAssist);
    util.move_right_motors(r_output * (12000.0 / 127) - headingAssist);

    if (fabs(forward.m_error) < 100){ forward.m_iterator++; } else { forward.m_iterator = 0;}
    if (fabs(forward.m_iterator) > 10){
      util.move_left_motors(0);
      util.move_right_motors(0);
      break;
    }
    if (fabs(forward.m_derivative) < 5) forward.m_failsafe++;
    if (forward.m_failsafe > 500){
      util.move_left_motors(0);
      util.move_right_motors(0);
      break;
    }
    pros::delay(10);
  }
}