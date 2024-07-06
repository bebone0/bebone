#include "vulkan_pipeline_tuples.h"

#include "vulkan_device.h"
#include "vulkan_texture.h"
#include "vulkan_pipeline_layout.h"
#include "vulkan_buffer_tuples.h"

namespace bebone::gfx {
    VulkanManagedPipelineTuple::VulkanManagedPipelineTuple(
        const shared_ptr<VulkanPipeline>& pipeline,
        const shared_ptr<VulkanPipelineLayout>& layout,
        const std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptors
    ) : pipeline(pipeline), layout(layout), descriptors(descriptors), bindless_samplers_index(0), bindless_uniforms_index(0) {

    }

    VulkanBindlessHandle VulkanManagedPipelineTuple::bind_texture(
        std::shared_ptr<VulkanDevice>& device,
        std::shared_ptr<VulkanTexture>& texture,
        const size_t& binding
    ) {
        auto dst_array_elements = std::vector<VulkanBindlessHandle> {};
        dst_array_elements.reserve(descriptors.size()); // FIF

        for(auto& _ : descriptors) {
            std::ignore = _;
            dst_array_elements.emplace_back(bindless_samplers_index);
        }

        ++bindless_samplers_index;

        device->update_descriptor_sets(texture, descriptors, binding, dst_array_elements);

        // Since there is a single texture, it has only single gpu handle, so there is no need
        // for returning entire dst_array_elements array
        return dst_array_elements[0];
    }

    std::vector<VulkanBindlessHandle> VulkanManagedPipelineTuple::bind_textures(
        std::shared_ptr<VulkanDevice>& device,
        std::vector<std::shared_ptr<VulkanTexture>>& textures,
        const size_t& binding
    ) {

        auto dst_array_elements = std::vector<VulkanBindlessHandle> {};
        dst_array_elements.reserve(descriptors.size()); // FIF

        for(auto& t : textures)
            dst_array_elements.push_back(bind_texture(device, t, binding));

        return dst_array_elements;
    }

    std::vector<VulkanBindlessHandle> VulkanManagedPipelineTuple::bind_uniform_buffer(
        std::shared_ptr<VulkanDevice>& device,
        const std::vector<VulkanBufferMemoryTuple>& tuples,
        const size_t& binding
    ) {
        auto dst_array_elements = std::vector<size_t> {};
        dst_array_elements.reserve(descriptors.size()); // FIF

        for(auto& _ : descriptors) {
            std::ignore = _;
            dst_array_elements.emplace_back(bindless_uniforms_index);
            ++bindless_uniforms_index;
        }

        device->update_descriptor_sets(tuples, descriptors, binding, dst_array_elements);

        return dst_array_elements;
    }

    void VulkanManagedPipelineTuple::destroy(VulkanDevice& device) {
        device.destroy_all(pipeline, layout);
        device.destroy_all(descriptors);

        mark_destroyed();
    }
}
