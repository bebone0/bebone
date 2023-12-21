#ifndef _GRAVITY_H_
#define _GRAVITY_H_

#include <memory>

#include "bebone/bebone.h"

#include "../component.h"
#include "../transform.h"

#include "../../game_time.h"

namespace game::core::ecs {
    using namespace bebone::core;
    using namespace std;

    class Gravity : public Component {
        private:
            float velocityY;
            const float gravity = 0.1f;
            shared_ptr<Transform> transform;

        public:
            Gravity(shared_ptr<Transform> transform);
            ~Gravity();

            void update();

            float get_velocity() const;
            void set_velocity(const float& velocity);
    };
}

#endif
