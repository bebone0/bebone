#ifndef _BEBONE_GFX_VULKAN_BUFFER_DEVICE_MEMORY_H_
#define _BEBONE_GFX_VULKAN_BUFFER_DEVICE_MEMORY_H_

#include <vector>

#include "../gfx_backend.h"

#include "interface/i_vulkan_device_memory.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanDevice;
    class VulkanBuffer;
    class VulkanImage;

    class VulkanDeviceMemory : public IVulkanDeviceMemory, private core::NonCopyable {
        private:
            VulkanDevice& device_owner;

            VkDeviceMemory device_memory;

        public:
            VulkanDeviceMemory(VulkanDevice& device, VkMemoryRequirements requirements, VkMemoryPropertyFlags properties);
            ~VulkanDeviceMemory();

            // Todo move to interface
            void bind_buffer_memory(VulkanBuffer& buffer);
            void bind_buffer_memory(std::unique_ptr<VulkanBuffer>& buffer);

            void bind_image_memory(VulkanImage& image);
            void bind_image_memory(std::unique_ptr<VulkanImage>& image);

            void map(const size_t& size, void** data);
            void unmap();

            void upload_data(const void* src, const size_t& size);

            VkDeviceMemory get_vulkan_device_memory() const override;
    };
}

#endif
