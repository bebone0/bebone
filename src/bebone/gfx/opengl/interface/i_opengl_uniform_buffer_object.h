#ifndef _BEBONE_GFX_I_OPENGL_UNIFORM_BUFFER_OBJECT_H_
#define _BEBONE_GFX_I_OPENGL_UNIFORM_BUFFER_OBJECT_H_

#include "../../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class IOpenGLUniformBufferObject {
        public:
            virtual ~IOpenGLUniformBufferObject() = default;

            virtual void bind_buffer_base(const i32& binding) const = 0;
            virtual void* map() const = 0;
            virtual void unmap() const = 0;
            virtual void bind() = 0;
            virtual void unbind() = 0;
            virtual void destroy() = 0;
    };
}

#endif
