#include "iostream"

namespace GirlPowered {
    class ClawController {
        public:
            enum class direction {
                OPEN,
                CLOSE
            };
            void move_claw(double speed, double time, direction dir);
    };
}