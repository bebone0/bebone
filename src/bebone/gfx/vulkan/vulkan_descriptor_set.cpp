#include "vulkan_descriptor_set.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_descriptor_set_layout.h"

namespace bebone::gfx::vulkan {
    VulkanDescriptorSet::VulkanDescriptorSet(
        const std::shared_ptr<VulkanDevice>& device,
        VulkanDescriptorPool& descriptor_pool,
        const std::shared_ptr<VulkanDescriptorSetLayout>& descriptor_set_layout
    ) {
        VkDescriptorSetAllocateInfo alloc_info{};
        alloc_info.type = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        alloc_info.descriptorPool = descriptor_pool.backend;
        alloc_info.descriptorSetCount = 1;
        alloc_info.pSetLayouts = &descriptor_set_layout->backend;

        VkDescriptorSetVariableDescriptorCountAllocateInfoEXT count_info;
        count_info.type = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO_EXT;
        count_info.ptr_next = nullptr;

        // Todo
        static unsigned int max_binding = 65536 - 1;
        count_info.descriptorSetCount = 1;

        count_info.pDescriptorCounts = &max_binding;
        alloc_info.ptr_next = &count_info; // Todo

        if (vkAllocateDescriptorSets(device->device, &alloc_info, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }
    }

    void VulkanDescriptorSet::destroy(VulkanDevice&) {

    }
}
