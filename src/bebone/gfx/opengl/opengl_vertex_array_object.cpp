#include "opengl_vertex_array_object.h"

namespace bebone::gfx {
    GLVertexArrayObject::GLVertexArrayObject() {
        glGenVertexArrays(1, &id);
    }

    GLVertexArrayObject::~GLVertexArrayObject() {
        destroy();
    }

    void GLVertexArrayObject::link_attributes(IOpenGLVertexBufferObject& vbo, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, const u64& offset) {
        vbo.bind();

        glVertexAttribPointer(layout, num_components, type, GL_FALSE, stride, (void*)(offset));
        glEnableVertexAttribArray(layout);

        vbo.unbind();
    }

    void GLVertexArrayObject::link_attributes(IOpenGLVertexBufferObject& vbo, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, void* offset) {
        vbo.bind();

        glVertexAttribPointer(layout, num_components, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);

        vbo.unbind();
    }

    void GLVertexArrayObject::bind() {
        glBindVertexArray(id);
    }

    void GLVertexArrayObject::unbind() {
        glBindVertexArray(0);
    }

    void GLVertexArrayObject::destroy() {
        glDeleteVertexArrays(1, &id);
    }
}
