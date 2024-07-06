#include "vulkan_texture.h"

#include "vulkan_device.h"
#include "vulkan_command_buffer_pool.h"

namespace bebone::gfx {
    using namespace bebone::core;
    using namespace bebone::assets;

    VulkanTexture::VulkanTexture(
        VulkanDevice& device,
        std::shared_ptr<VulkanCommandBufferPool>& command_buffer_pool,
        const std::shared_ptr<Image<ColorRGBA>>& raw
    ) {
        auto [im, mem] = device.create_image_memory(ColorRGBA::get_vulkan_format(),
            { static_cast<uint32_t>(raw->get_width()), static_cast<uint32_t>(raw->get_height()), 1},
            { .usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT }
        );

        image = im; memory = mem;

        image->transition_layout(*command_buffer_pool, device, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

        auto size = raw->get_width() * raw->get_height() * sizeof(ColorRGBA);
        auto staged = device.create_buffer_memory(size);
        staged->upload_data(device, raw->data(), size);

        // Todo Probably uploading data to gpu need some sort of render graph api
        command_buffer_pool->copy_buffer_to_image(device, staged->buffer, image);

        device.destroy_all(staged);
        device.collect_garbage();

        image->transition_layout(*command_buffer_pool, device, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

        sampler = device.create_sampler();
        view = device.create_image_view(*image, ColorRGBA::get_vulkan_format());
    }

    VulkanTexture::VulkanTexture(VulkanDevice& device,
        std::shared_ptr<VulkanCommandBufferPool>& command_buffer_pool,
        VkExtent3D extent,
        VkFormat image_format
    ) {
        auto [im, mem] = device.create_image_memory(image_format, extent, // Todo, image_format should be configurable
            { .usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT }
        );  // Todo, usage should be configurable

        image = im; memory = mem;

        sampler = device.create_sampler();
        view = device.create_image_view(*image, image_format);
    }

    void VulkanTexture::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        sampler->destroy(device);
        view->destroy(device);
        memory->destroy(device);
        image->destroy(device);

        mark_destroyed();
    }
}
