#ifndef _BEBONE_GFX_OPENGL_VERTEX_ARRAY_OBJECT_H_
#define _BEBONE_GFX_OPENGL_VERTEX_ARRAY_OBJECT_H_

#include "interface/i_opengl_vertex_array_object.h"

namespace bebone::gfx {
    using namespace bebone::core;

    /// VAO
    class GLVertexArrayObject : public IOpenGLVertexArrayObject {
        private:
            u32 id;

        public:
            /// Generates VAO and assigns unique ID
            GLVertexArrayObject();

            /// Destroys VAO
            ~GLVertexArrayObject() override;

            /*!
             * Interpret the vertex buffer data
             * @param vbo - vertex buffer object
             * @param layout - vertex shader layout
             * @param num_components - number of components
             * @param type - data type
             * @param stride - byte offset between consecutive vertex attributes
             * @param offset - an offset of the first component of the first vertex attribute in the array
             */
            void link_attributes(IOpenGLVertexBufferObject& vbo, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, const u64& offset) override;

            /*!
             * Interpret the vertex buffer data
             * @param vbo - vertex buffer object
             * @param layout - vertex shader layout
             * @param num_components - number of components
             * @param type - data type
             * @param stride - byte offset between consecutive vertex attributes
             * @param offset - an offset of the first component of the first vertex attribute in the array
            */
            void link_attributes(IOpenGLVertexBufferObject& vbo, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, void* offset) override;

            /// Binds VAO
            void bind() override;

            /// Unbinds VAO
            void unbind() override;

            /// Destroys VAO. Calls automatically in the destructor
            void destroy() override;
    };
}

#endif
