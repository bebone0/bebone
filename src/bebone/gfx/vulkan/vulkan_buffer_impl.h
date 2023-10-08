#ifndef _BEBONE_GFX_VULKAN_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_BUFFER_IMPLEMENTATION_H_

#include <vector>

#include "vulkan_device.h"
#include "../../core/core.h"
#include "../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    static std::vector<VkVertexInputBindingDescription> getBindingDescriptions() {
        std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
        
        bindingDescriptions[0].binding = 0;
        bindingDescriptions[0].stride = sizeof(Vec3f) * 2;
        bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescriptions;
    }

    static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions() {
        std::vector<VkVertexInputAttributeDescription> atrributeDescriptions(2);
        
        atrributeDescriptions[0].binding = 0;
        atrributeDescriptions[0].location = 0;
        atrributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        atrributeDescriptions[0].offset = 0;

        atrributeDescriptions[1].binding = 0;
        atrributeDescriptions[1].location = 1;
        atrributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        atrributeDescriptions[1].offset = sizeof(Vec3f);

        return atrributeDescriptions;
    }

    class VulkanBufferImpl : private core::NonCopyable {
        private:
            VulkanDevice& device;

            VkBuffer buffer;
            VkDeviceMemory bufferMemory;

            const size_t _size;

        public:
            VulkanBufferImpl(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VulkanDevice& device) : device(device), _size(static_cast<size_t>(size)) {
                VkBufferCreateInfo bufferInfo{};
                bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
                bufferInfo.size = size;
                bufferInfo.usage = usage;
                bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

                if (vkCreateBuffer(device.device(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create vulkan buffer!");
                }

                VkMemoryRequirements memRequirements;
                vkGetBufferMemoryRequirements(device.device(), buffer, &memRequirements);

                VkMemoryAllocateInfo allocInfo{};
                allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
                allocInfo.allocationSize = memRequirements.size;
                allocInfo.memoryTypeIndex = device.findMemoryType(memRequirements.memoryTypeBits, properties);

                if (vkAllocateMemory(device.device(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
                    throw std::runtime_error("failed to allocate vulkan buffer memory!");
                }

                vkBindBufferMemory(device.device(), buffer, bufferMemory, 0);
            }

            ~VulkanBufferImpl() {
                vkDestroyBuffer(device.device(), buffer, nullptr);
                vkFreeMemory(device.device(), bufferMemory, nullptr);
            }

            VkBuffer get_buffer() const {
                return buffer;
            }

            size_t get_size() {
                return _size;
            }

            VulkanDevice& get_device() {
                return device;
            }

            VkDeviceMemory get_buffer_memory() const {
                return bufferMemory;
            }
    };
}

#endif
