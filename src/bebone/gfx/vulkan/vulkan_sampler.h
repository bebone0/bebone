#ifndef _BEBONE_GFX_VULKAN_SAMPLER_H_
#define _BEBONE_GFX_VULKAN_SAMPLER_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_device_memory.h"

#include "interface/i_vulkan_sampler.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanSampler : public IVulkanSampler, private core::NonCopyable {
        private:
            IVulkanDevice& device_owner;

            VkSampler sampler;

        public:
            VulkanSampler(IVulkanDevice& device);
            ~VulkanSampler();

            VkSampler get_vk_image_sampler() const override;
    };
}

#endif
