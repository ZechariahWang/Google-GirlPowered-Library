#include "iostream"

namespace GirlPowered {
    class RotationPID {
        public:

            double r_kp;
            double r_ki;
            double r_kd;

            double r_derivative = 0;
            double r_integral = 0;
            double r_error = 0;
            double r_prev_error = 0;
            double r_iterator = 0;
            double r_failsafe = 0;
            double r_max_speed = 0;

            RotationPID();
            void set_rotation_pid_constants(double p, double i, double d);
            void reset_rotation_values();
            double current_robot_heading();
            double compute_rotation_pid(double current, double target);
            void turn(double target, double speed);
    };
}