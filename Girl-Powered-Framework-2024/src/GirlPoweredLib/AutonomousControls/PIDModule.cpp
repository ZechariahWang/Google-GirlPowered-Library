/**
 * @file PIDModule.cpp
 * @author Zechariah Wang
 * @brief Universal PID logic, for autonomous subsystems
 * @version 0.1
 * @date 2023-07-14
 */

#include "main.h"

/**
 * @brief PID Constructor
 * 
 * @param kp Proportional value
 * @param ki Integral value
 * @param kd Derivative value
 * @param threshold Minimum value needed to enter exit stage
 * @param tolerance Minimum value to leave exit stage
 * @param failsafe_threshold If PID gets stuck, the minimum value needed to enter exit stage
 * @param failsafe_tolerance If PID gets stuck, the minimum value needed to leave exit stage
 * @param max_speed max speed of PID
 */

using namespace GirlPowered;

GirlPowered::PID::PID(double kp, double ki, double kd, double threshold, double tolerance, double failsafe_threshhold, double failsafe_tolerance, double max_speed){
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->main_threshold = threshold;
    this->main_tolerance = tolerance;
    this->failsafe_threshhold = failsafe_threshhold;
    this->failsafe_tolerance = failsafe_tolerance;
    this->max_speed = max_speed;
}

/**
 * @brief Reset PID values
 * 
 */

void GirlPowered::PID::reset_values(){
    this->output = 0;
    this->error = 0;
    this->integral = 0;
    this->derivative = 0;
    this->previous_error = 0;
    this->iterator = 0;
    this->failsafe = 0;
}

/**
 * @brief computes PID logic
 * 
 * @param current current position value
 * @param target target position value
 */

double GirlPowered::PID::compute_pid(double current, double target){
  this->error = target - current;
  this->derivative = this->error - this->previous_error;
  if (this->ki != 0){
    this->integral += this->error;
  }
  if (util.sgn(this->error) != util.sgn(this->previous_error)){
    this->integral = 0;
  }
  double output = (this->kp * this->error) + (this->integral * this->ki) + (this->derivative * this->kd);

  if (output * (12000.0 / 127) >= this->max_speed * (12000.0 / 127)) { output = this->max_speed; }
  if (output * (12000.0 / 127) <= -this->max_speed * (12000.0 / 127)) { output = -this->max_speed; }
  this->previous_error = this->error;
  return output;
}

/**
 * @brief PID driver logic
 * 
 * @param reference_motor address of reference motor
 * @param target target of reference motor
 */

void GirlPowered::PID::set_pid(double target){
  this->reset_values();
  while (true){
    double currentPos = chassis_left_motors.at(0).get_position();
    double vol = this->compute_pid(currentPos, target);
    chassis_left_motors.at(0).move_voltage(vol);
    chassis_right_motors.at(0).move_voltage(vol);
    if (fabs(this->error) < this->main_threshold) { this->iterator++; } else { this->iterator = 0;}
    if (fabs(this->iterator) >= this->main_tolerance){
      chassis_left_motors.at(0).move_voltage(0);
      chassis_right_motors.at(0).move_voltage(0);
      break;
    }
    if (fabs(this->derivative) < this->failsafe_threshhold) {this->failsafe++;}
    if (this->failsafe > this->failsafe_tolerance){
      chassis_left_motors.at(0).move_voltage(0);
      chassis_right_motors.at(0).move_voltage(0);
      break;
    }
    pros::delay(10);
  }
}