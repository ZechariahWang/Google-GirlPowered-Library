#include "iostream"

namespace GirlPowered {
    class ArmController {
        public:
            enum class direction {
                UP,
                DOWN
            };
            void move_arm(double speed, double time, direction dir);
    };
}