#ifndef _BEBONE_GFX_SHADER_CODE_H_
#define _BEBONE_GFX_SHADER_CODE_H_

#include <vector>

#include "../../core/core.h"
#include "../gfx_backend.h"

#include "shader_type.h"

namespace bebone::gfx {
    using namespace bebone::core;

    using RawSpirVByteCode = std::vector<u32>;

    class ShaderCode {
        private:
            RawSpirVByteCode m_spirVCode;
            ShaderType m_shaderType;

        public:
            ShaderCode(const ShaderType& p_shaderType) 
                : m_shaderType(p_shaderType) {

            }

            ShaderCode(const RawSpirVByteCode& p_spirVByteCode, const ShaderType& p_shaderType) 
                : m_spirVCode(p_spirVByteCode), 
                  m_shaderType(p_shaderType) {

            }

            const RawSpirVByteCode& get_byte_code() const {
                return m_spirVCode;
            }
    };
}

#endif