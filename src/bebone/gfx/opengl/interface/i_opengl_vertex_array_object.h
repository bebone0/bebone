#ifndef _BEBONE_GFX_I_OPENGL_VERTEX_ARRAY_OBJECT_H_
#define _BEBONE_GFX_I_OPENGL_VERTEX_ARRAY_OBJECT_H_

#include "i_opengl_vertex_buffer_object.h"
#include "../../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class IOpenGLVertexArrayObject {
        public:
            virtual ~IOpenGLVertexArrayObject() = default;
            virtual void link_attributes(IOpenGLVertexBufferObject& vbo, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, const u64& offset) = 0;
            virtual void link_attributes(IOpenGLVertexBufferObject& vbo, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, void* offset) = 0;

            virtual void bind() = 0;
            virtual void unbind() = 0;
            virtual void destroy() = 0;
    };
}

#endif
