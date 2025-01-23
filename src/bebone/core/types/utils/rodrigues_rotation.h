#ifndef _BEBONE_CORE_TYPES_RODRIGUES_ROTATION_
#define _BEBONE_CORE_TYPES_RODRIGUES_ROTATION_

#include "interpolation.tpp"
#include "../matrix/matrix_4x4.h"

namespace bebone::core {
    static inline Matrix<f32, 4, 4> rodrigues_rotation(const Vec3f& front, const Vec3f& target) {
        const auto front_norm = front.normalize();
        const auto target_norm = target.normalize();

        auto axis = Vec3f::cross(front_norm, target_norm);
        const auto dot = Vec3f::dot(front_norm, target_norm);
        const auto angle = std::acos(bebone::core::clamp(dot, -1.0f, 1.0f));

        if (axis.x != 0 || axis.y != 0 || axis.z != 0) {
            axis = axis.normalize();
        } else {
            if (dot > 0)
                return Matrix<f32, 4, 4>::identity();

            axis = {1, 0, 0};
        }

        const auto c = std::cos(angle);
        const auto s = std::sin(angle);
        const auto t = 1.0f - c;

        const auto x = axis.x, y = axis.y, z = axis.z;

        return {
            t * x * x + c,     t * x * y - s * z, t * x * z + s * y, 0,
            t * x * y + s * z, t * y * y + c,     t * y * z - s * x, 0,
            t * x * z - s * y, t * y * z + s * x, t * z * z + c,     0,
            0,                 0,                 0,                 1
        };
    }
}

#endif
