#ifndef _BEBONE_RENDERER_ICAMERA_H_
#define _BEBONE_RENDERER_ICAMERA_H_

#include "renderer_backend.h"
#include "vertex.h"
#include "icommand_encoder.h"

namespace bebone::renderer {
    class ICamera {
        private:
            Vec3f cam_position;
            Vec3f cam_rotation;
            Vec3f cam_direction;

        protected:

        public:
            ICamera();
            virtual ~ICamera() = default;

            virtual Mat4f calculate_matrix(const f32& aspect_ratio) const = 0;

            void apply_position(const Vec3f& position);
            void apply_rotation(const Vec3f& rotation);
            void apply_direction(const Vec3f& direction);

            void set_position(const Vec3f& position);
            void set_rotation(const Vec3f& rotation);
            void set_direction(const Vec3f& direction);

            const Vec3f& get_position() const;
            const Vec3f& get_rotation() const;
            const Vec3f& get_direction() const;
    };
}

#endif