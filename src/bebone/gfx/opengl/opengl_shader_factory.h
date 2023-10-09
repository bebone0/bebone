#ifndef _BEBONE_OPENGL_SHADER_FACTORY_H_
#define _BEBONE_OPENGL_SHADER_FACTORY_H_

#include "../shaders/shader_type.h"
#include "../shaders/shader_compiler.h"

#include "opengl_shader.h"

namespace bebone::gfx::opengl {
    class GLShaderFactory {
        private:
            static std::string read_file(const std::string& path);

        public:
            GLShaderFactory() = delete;

            static GLShader create_shader(const std::string& path, const ShaderType& shaderType);
    };
}

#endif
