#ifndef _BEBONE_GFX_VULKAN_RENDER_TARGET_H_
#define _BEBONE_GFX_VULKAN_RENDER_TARGET_H_

#include <array>

#include "../gfx_backend.h"

#include "vulkan_render_pass.h"
#include "vulkan_device.h"
#include "vulkan_image.h"
#include "vulkan_framebuffer.h"

namespace bebone::gfx {
    class VulkanImage;

    class VulkanRenderTarget : public VulkanApi {
        public:
            std::vector<VulkanSwapChainImageTuple> color_attachments; // Todo, framebuffer can have multiple color_attachments
            std::vector<VulkanDepthImageTuple> depth_attachments;
            std::vector<std::shared_ptr<VulkanFramebuffer>> framebuffers;

            // This is still just a swap chain render target constructor
            VulkanRenderTarget(
                VulkanDevice& device,
                std::vector<VulkanSwapChainImageTuple>& image_views,
                std::shared_ptr<VulkanRenderPass>& render_pass,
                VkExtent2D extent);

            void destroy(VulkanDevice& device);
    };
}

#endif
