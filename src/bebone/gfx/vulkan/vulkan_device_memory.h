#ifndef _BEBONE_GFX_VULKAN_BUFFER_DEVICE_MEMORY_H_
#define _BEBONE_GFX_VULKAN_BUFFER_DEVICE_MEMORY_H_

#include <vector>

#include "../gfx_backend.h"

#include "interface/i_vulkan_device_memory.h"
#include "interface/i_vulkan_device.h"
#include "interface/i_vulkan_buffer.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanBuffer;
    class VulkanImage;

    class VulkanDeviceMemory : public IVulkanDeviceMemory, private core::NonCopyable {
        private:
            IVulkanDevice& device_owner;

            VkDeviceMemory device_memory;

        public:
            VulkanDeviceMemory(IVulkanDevice& device, VkMemoryRequirements requirements, VkMemoryPropertyFlags properties);
            ~VulkanDeviceMemory() override;

            // Vulkan Device Memory
            VkDeviceMemory get_vk_device_memory() const override;
            void bind_buffer_memory(IVulkanBuffer& buffer) override;
            void bind_image_memory(IVulkanImage& image) override;
            void map(const size_t& size, void** data) override;
            void unmap() override;
            void upload_data(const void* src, const size_t& size) override;
    };
}

#endif
