#ifndef _BEBONE_GFX_COLOR_EXTENSIONS_H_
#define _BEBONE_GFX_COLOR_EXTENSIONS_H_

#include "gfx_backend.h"

namespace bebone::gfx{
    using namespace bebone::core;

    template<typename ColorType>
    inline constexpr u32 get_gl_format() {
        return GL_ZERO;
    }

    template<typename ColorType>
    inline constexpr VkFormat get_vulkan_format() {
        return VK_FORMAT_UNDEFINED;
    }

    template<typename ColorType>
    inline constexpr u32 get_gl_type() {
        return GL_ZERO;
    }

    template<>
    inline constexpr u32 get_gl_format<ColorRGB24>() {
        return GL_RGB;
    }

    template<>
    inline constexpr VkFormat get_vulkan_format<ColorRGB24>() {
        return VK_FORMAT_R8G8B8_SRGB;
    }

    template<>
     inline constexpr u32 get_gl_type<ColorRGB24>() {
        return GL_UNSIGNED_BYTE;
    }

    template<>
    inline constexpr u32 get_gl_format<ColorRGBA32>() {
        return GL_RGBA;
    }

    template<>
    inline constexpr VkFormat get_vulkan_format<ColorRGBA32>() {
        return VK_FORMAT_R8G8B8A8_SRGB;
    }

    template<>
    inline constexpr u32 get_gl_type<ColorRGBA32>() {
        return GL_UNSIGNED_BYTE;
    }

    template<>
    inline constexpr u32 get_gl_format<ColorRGBA32F>() {
        return GL_RGBA;
    }

    template<>
    inline constexpr VkFormat get_vulkan_format<ColorRGBA32F>() {
        return VK_FORMAT_R32G32B32A32_SFLOAT;
    }

    template<>
    inline constexpr u32 get_gl_type<ColorRGBA32F>() {
        return GL_FLOAT;
    }
}

#endif
