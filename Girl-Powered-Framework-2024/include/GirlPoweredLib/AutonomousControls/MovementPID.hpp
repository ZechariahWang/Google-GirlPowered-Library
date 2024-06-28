#include "iostream"

namespace GirlPowered {
    class MovementPID {
        public:
            double m_kp;
            double m_ki;
            double m_kd;

            double m_derivative = 0;
            double m_integral = 0;
            double m_error = 0;
            double m_prev_error = 0;
            double m_iterator = 0;
            double m_failsafe = 0;
            double m_max_speed = 0;

            MovementPID();
            void set_movement_pid_constants(double p, double i, double d);
            double compute_movement_pid(double current, double target);
            void reset_movement_values();
            void move(double target, double speed);
    };
}