/**
 * @file AssetDirectoryConfig.cpp
 * @author Zechariah Wang
 * @brief Drivetrain config driver
 * @version 0.1
 * @date 2024-04-05
 */

#include "main.h"

using namespace GirlPowered;

std::vector<pros::Motor> chassis_left_motors;
std::vector<pros::Motor> chassis_right_motors;
std::vector<pros::Motor> arm_motors;
std::vector<pros::Motor> claw_motors;

bool is_reversed(int value){
  if (value < 0){ return true; }
  return false;
}

AssetConfig::AssetConfig(std::vector<int> left_chassis_ports, std::vector<int> right_chassis_ports, std::vector<int> arm_ports, std::vector<int> claw_ports) {

    for (auto i : left_chassis_ports) {
        pros::Motor temp(abs(i), is_reversed(i));
        chassis_left_motors.push_back(temp);
    }
    for (auto i : right_chassis_ports) {
        pros::Motor temp(abs(i), is_reversed(i));
       chassis_right_motors.push_back(temp);
    }
    for (auto i : arm_ports) {
        pros::Motor temp(abs(i), is_reversed(i));
       arm_motors.push_back(temp);
    }
    for (auto i : claw_ports) {
        pros::Motor temp(abs(i), is_reversed(i));
       claw_motors.push_back(temp);
    }

    config.left_reversed = true;
    config.right_reversed = false;

}

