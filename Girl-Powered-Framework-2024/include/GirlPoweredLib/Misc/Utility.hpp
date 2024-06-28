#include "iostream"
#include "vector"

namespace GirlPowered {
    class Utility{
        public:
            int sgn(double num);
            bool is_reversed(int value);
            void move_left_motors(double voltage);
            void move_right_motors(double voltage);
            void move_arm_motors(double voltage);
            void move_claw_motors(double voltage);
            double get_encoder_position();
    };
}