#include "vulkan_render_target.h"

#include "vulkan_image.h"
#include "vulkan_image_view.h"
#include "vulkan_device_memory.h"
#include "vulkan_swap_chain.h"
#include "vulkan_depth_image.h"
#include "vulkan_framebuffer.h"

namespace bebone::gfx {
    VulkanRenderTarget::VulkanRenderTarget(
        IVulkanDevice& device,
        std::unique_ptr<VulkanRenderPass>& render_pass
    ) {
        // Create color attachments
        color_attachments.reserve(render_pass->get_color_attachments_count());

        for(auto& attachment : render_pass->get_attachments()) {
            if (attachment.type != Color)
                continue;

            auto frame_attachments = std::vector<std::unique_ptr<IVulkanImageView>>{};
            frame_attachments.reserve(3); // Todo, 3 should be configurable

            for (size_t f = 0; f < 3; ++f) {// Todo, 3 should be configurable
                auto tt = std::make_unique<VulkanTexture>(device, attachment.extent, attachment.description.format);
                std::unique_ptr<IVulkanImageView> texture(static_cast<IVulkanImageView*>(tt.release())); // Todo
                frame_attachments.push_back(std::move(texture));
            }

            color_attachments.push_back(std::move(frame_attachments));
        }

        // Create depth attachments
        if(render_pass->get_depth_attachment().has_value()) {
            auto attachment = render_pass->get_depth_attachment().value();

            auto frame_attachments = std::vector<std::unique_ptr<IVulkanImageView>> {};
            frame_attachments.reserve(3); // Todo, 3 should be configurable

            for(size_t f = 0; f < 3; ++f)  { // Todo, 3 should be configurable
                auto dit = std::make_unique<VulkanDepthImage>(device, attachment.extent);
                std::unique_ptr<IVulkanImageView> depth(static_cast<IVulkanImageView*>(dit.release())); // Todo
                frame_attachments.push_back(std::move(depth));
            }

            depth_attachments = std::move(frame_attachments);
        }

        // Create frame buffers
        for(size_t i = 0; i < 3; ++i) { // Todo, 3 should be configurable
            auto attachments = std::vector<std::unique_ptr<IVulkanImageView>> {};
            attachments.reserve(color_attachments.size());

            for(auto& color_attachment : color_attachments) {
                auto& attachment = color_attachment[i];
                attachments.push_back(std::move(attachment));
            }

            // Todo, depth attachment order should be configurable
            if(!depth_attachments.empty())
                attachments.push_back(std::move(depth_attachments[i]));

            auto framebuffer = std::make_unique<VulkanFramebuffer>(device, attachments, render_pass, render_pass->get_extent());
            framebuffers.push_back(std::move(framebuffer));
        }

        LOG_TRACE("Created Vulkan render target");
    }

    VulkanRenderTarget::VulkanRenderTarget(
        IVulkanDevice& device,
        std::unique_ptr<VulkanRenderPass>& render_pass,
        std::vector<std::unique_ptr<VulkanSwapChainImage>>& images
    ) {
        // We do need to create color attachments, since swap chain handles them

        // Create depth attachments
        if(render_pass->get_depth_attachment().has_value()) {
            auto attachment = render_pass->get_depth_attachment().value();

            auto frame_attachments = std::vector<std::unique_ptr<IVulkanImageView>> {};
            frame_attachments.reserve(3); // Todo, 3 should be configurable

            for(size_t f = 0; f < 3; ++f) // Todo, 3 should be configurable
            {
                frame_attachments.push_back(std::make_unique<VulkanDepthImage>(device, attachment.extent));
            }

            depth_attachments = std::move(frame_attachments);
        }

        // Create frame buffers
        for(size_t i = 0; i < 3; ++i) { // Todo, 3 should be configurable
            // auto attachments = std::vector { image_views[i]->get_view().value(), depth_attachments[i]->get_view().value() };

            auto attachments = std::vector<std::unique_ptr<IVulkanImageView>> {};
            attachments.push_back(std::move(images[i]));

            if(!depth_attachments.empty())
                attachments.push_back(std::move(depth_attachments[i]));

            auto framebuffer = std::make_unique<VulkanFramebuffer>(device, attachments, render_pass, render_pass->get_extent());

            framebuffers.push_back(std::move(framebuffer));

            // Todo, there we need to safe color_attachment since we how own it
            color_attachments.push_back(std::move(attachments));
        }

        LOG_TRACE("Created Vulkan render target");
    }

    VulkanRenderTarget::~VulkanRenderTarget() {
        // Todo
        for(auto& frame : color_attachments)
            for(auto& tuple : frame)
                tuple.reset(); // Since image is provided by swap chain we should not destroy it, only view

        for(auto& tuple : depth_attachments)
            tuple.reset();

        for (auto& framebuffer : framebuffers)
            framebuffer.reset();

        LOG_DEBUG("Destroyed Vulkan render target");
    }
}
