#ifndef _BEBONE_GFX_VULKAN_DESCRIPTOR_SET_LAYOUT_H_
#define _BEBONE_GFX_VULKAN_DESCRIPTOR_SET_LAYOUT_H_

#include "../gfx_backend.h"

#include "vulkan_descriptor_pool.h"

namespace bebone::gfx {
    class VulkanDevice;
    class VulkanDescriptorSetLayoutBinding;

    class VulkanDescriptorSetLayout : private core::NonCopyable {
        public:
            VkDescriptorSetLayout backend;

        private:
            IVulkanDevice& device_owner;

        public:
            VulkanDescriptorSetLayout( // Todo move to private
                IVulkanDevice& device,
                const std::vector<VulkanDescriptorSetLayoutBinding>& all_bindings);

            ~VulkanDescriptorSetLayout();
    };
}

#endif
