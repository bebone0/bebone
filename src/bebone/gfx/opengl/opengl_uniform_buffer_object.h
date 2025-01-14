#ifndef _BEBONE_GFX_OPENGL_UNIFORM_BUFFER_OBJECT_H_
#define _BEBONE_GFX_OPENGL_UNIFORM_BUFFER_OBJECT_H_

#include "interface/i_opengl_uniform_buffer_object.h"

namespace bebone::gfx {
    using namespace bebone::core;

    /// UBO
    class GLUniformBufferObject : public IOpenGLUniformBufferObject {
        private:
            u32 id;
            u64 size;

        public:
            /*!
             * Default constructor
             * @param size - desired buffer size
            */
            GLUniformBufferObject(const u64& size);

            ~GLUniformBufferObject() override;

            /*!
             * Binds buffer to specific binding
             * @param binding - binding index
            */
            void bind_buffer_base(const i32& binding) const override;

            /*!
             * Maps buffer to accessible memory region
             * @return - pointer to mapped memory region
            */
            void* map() const override;

            /// Unmaps uniform buffer
            void unmap() const override;

            /// Binds UBO
            void bind() override;

            /// Unbinds UBO
            void unbind() override;

            /// Destroys UBO. Calls automatically in the destructor
            void destroy() override;
    };
}

#endif
