#include "flying.h"

#include "../../input_system/input.h"

namespace game::core::ecs {
    Flying::Flying(shared_ptr<Transform> transform, float flyForce) : velocityY(0.0f), flyForce(flyForce), transform(transform) {
        using namespace game::core::input_system;

        auto flyFunction = [this]() {
            set_velocity(this->flyForce);
        };
        Input::register_mouse_action(MouseKeyCode::LEFT_MOUSE_BUTTON, Action(flyFunction));
    }

    Flying::~Flying() {
        transform = nullptr;
    }

    void Flying::update() {
        velocityY += Time::deltaTime * -gravity;
        transform->set_position(Vec3f(transform->get_position().x, transform->get_position().y + velocityY, transform->get_position().z));
    }

    float Flying::get_velocity() const {
        return velocityY;
    }

    void Flying::set_velocity(const float& velocity) {
        velocityY = velocity;
    }
}