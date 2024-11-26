#ifndef _BEBONE_GFX_I_VULKAN_DEVICE_MEMORY_H_
#define _BEBONE_GFX_I_VULKAN_DEVICE_MEMORY_H_

#include "../../gfx_backend.h"

#include "i_vulkan_buffer.h"
#include "i_vulkan_image.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class IVulkanDeviceMemory {
        public:
            virtual ~IVulkanDeviceMemory() = default;

            [[nodiscard]] virtual VkDeviceMemory get_vk_device_memory() const = 0;
            virtual void bind_buffer_memory(IVulkanBuffer& buffer) = 0;
            virtual void bind_image_memory(IVulkanImage& image) = 0;
            virtual void map(const size_t& size, void** data) = 0;
            virtual void unmap() = 0;
            virtual void upload_data(const void* src, const size_t& size) = 0;
            
    };
}

#endif
