#ifndef _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_POOL_H_
#define _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_POOL_H_

#include <vector>

#include "../gfx_backend.h"
#include "../command_buffer_pool.h"

#include "../device_impl.h"

#include "vulkan_command_buffer.h"

#include "vulkan_uniform_buffer_pool.h"

namespace bebone::gfx {
    class VulkanDescriptorPool : public DescriptorPool {
        private:
            DeviceImpl& _device;

            VkDescriptorPool descriptorPool;
            std::vector<VkDescriptorSet> descriptorSets;

        public:
            //* Count should be pre computed 
            VulkanDescriptorPool(DeviceImpl& device, const size_t& descriptorPoolCount) : _device(device) {
                VkDescriptorPoolSize poolSize{};
                poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                poolSize.descriptorCount = static_cast<uint32_t>(descriptorPoolCount);

                VkDescriptorPoolCreateInfo poolInfo{};
                poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
                poolInfo.poolSizeCount = 1;
                poolInfo.pPoolSizes = &poolSize;
                poolInfo.maxSets = static_cast<uint32_t>(descriptorPoolCount);

                if (vkCreateDescriptorPool(_device.device(), &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create descriptor pool!");
                }
            }

            void create_descriptor(VkDescriptorSetLayout& descriptorSetLayout, VkBuffer buffer) {
                VkDescriptorSetAllocateInfo allocInfo{};
                allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
                allocInfo.descriptorPool = descriptorPool;
                allocInfo.descriptorSetCount = 1;
                allocInfo.pSetLayouts = &descriptorSetLayout;

                descriptorSets.push_back({});

                auto& descriptorSet = descriptorSets[descriptorSets.size() - 1];

                /** Aka taking last */
                if (vkAllocateDescriptorSets(_device.device(), &allocInfo, &descriptorSet) != VK_SUCCESS) {
                    throw std::runtime_error("failed to allocate descriptor sets!");
                }

                // So for each  buffer we should create this thing, and update 'descriptorWrite.descriptorCount' and 'descriptorWrite.pBufferInfo'
                VkDescriptorBufferInfo bufferInfo{};
                bufferInfo.buffer = buffer;
                bufferInfo.offset = 0;
                bufferInfo.range = sizeof(float);

                VkWriteDescriptorSet descriptorWrite{};
                descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                descriptorWrite.dstSet = descriptorSet;
                descriptorWrite.dstBinding = 0;
                descriptorWrite.dstArrayElement = 0;
                descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                descriptorWrite.descriptorCount = 1;
                descriptorWrite.pBufferInfo = &bufferInfo;
                descriptorWrite.pImageInfo = nullptr; // Optional
                descriptorWrite.pTexelBufferView = nullptr; // Optional

                vkUpdateDescriptorSets(_device.device(), 1, &descriptorWrite, 0, nullptr);
            }

            VkDescriptorSet& get_descriptor_set(const size_t& index) override {
                return descriptorSets[index];
            }

            ~VulkanDescriptorPool() {
                vkDestroyDescriptorPool(_device.device(), descriptorPool, nullptr);
            }
    };  
}

#endif
