/**
 * @file AssetDirectoryConfig.cpp
 * @author Zechariah Wang
 * @brief Assigns motors to their designated subsystem. You can edit these ports in main.cpp
 * @brief You do not need to edit these functions
 * 
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

