#ifndef _BEBONE_GFX_VULKAN_FRAMEBUFFER_H_
#define _BEBONE_GFX_VULKAN_FRAMEBUFFER_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanDevice;

    class VulkanImageView;
    class VulkanRenderPass;

    class VulkanFramebuffer : public VulkanWrapper<VkFramebuffer>, private core::NonCopyable {
        private:
            VulkanDevice& device_owner;

        public:
            VulkanFramebuffer(
                VulkanDevice& device,
                const std::vector<std::shared_ptr<VulkanImageView>>& attachment_views,
                const std::unique_ptr<VulkanRenderPass>& render_pass,
                VkExtent2D extent);

            ~VulkanFramebuffer();

            // void destroy(VulkanDevice& device) override;
    };
}

#endif
