#include "main.h"

int GirlPowered::Utility::sgn(double num){ return (num < 0) ? -1 : ((num > 0) ? 1 : 0); }

void GirlPowered::Utility::move_left_motors(double voltage){
  for (auto i : chassis_left_motors) {
    i.move_voltage(voltage);
  }
}

void GirlPowered::Utility::move_right_motors(double voltage){
  for (auto i : chassis_right_motors) {
    i.move_voltage(voltage);
  }
}

void GirlPowered::Utility::move_arm_motors(double voltage){
  for (auto i : arm_motors) {
    i.move_voltage(voltage);
  }
}

void GirlPowered::Utility::move_claw_motors(double voltage){
  for (auto i : claw_motors) {
    i.move_voltage(voltage);
  }
}

double GirlPowered::Utility::get_encoder_position() {
  double left_values = 0;
  double right_values = 0;
  int left_num = 0; // number of motors
  int right_num = 0; // number of motors

  double left_pos = chassis_left_motors.at(0).get_position();
  double right_pos = chassis_right_motors.at(0).get_position();

  return (left_pos + right_pos) / 2;
}