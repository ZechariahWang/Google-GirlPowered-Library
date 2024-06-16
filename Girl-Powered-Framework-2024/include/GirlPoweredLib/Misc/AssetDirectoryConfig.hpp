#include "iostream"
#include "vector"

#pragma once
#include "main.h"

namespace GirlPowered {
    class AssetConfig{
        public:
            AssetConfig();
            AssetConfig(std::vector<int> left_chassis_ports, std::vector<int> right_chassis_ports, std::vector<int> arm_ports, std::vector<int> claw_motors);

            int8_t arm_motor;
            int8_t claw_motor;

            bool left_reversed;
            bool right_reversed;
    };
}

extern GirlPowered::AssetConfig config;
extern std::vector<pros::Motor> chassis_left_motors;
extern std::vector<pros::Motor> chassis_right_motors;
extern std::vector<pros::Motor> arm_motors;
extern std::vector<pros::Motor> claw_motors;