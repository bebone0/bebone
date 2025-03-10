#ifndef _BEBONE_GFX_I_OPENGL_ELEMENT_BUFFER_OBJECT_H_
#define _BEBONE_GFX_I_OPENGL_ELEMENT_BUFFER_OBJECT_H_

#include "../../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class IOpenGLElementBufferObject {
        public:
            virtual ~IOpenGLElementBufferObject() = default;

            virtual void buffer_sub_data(const GLintptr& offset, const GLsizeiptr& size, const void* data) = 0;

            virtual void bind() = 0;
            virtual void unbind() = 0;
            virtual void destroy() = 0;
    };
}

#endif
