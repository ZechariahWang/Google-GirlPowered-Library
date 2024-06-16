#include "iostream"

namespace GirlPowered {
    class DriverController {
        public:
            int init;
            void drivetrain_controller();
            void arm_controller(int speed);
            void claw_controller(int speed);
    };
}