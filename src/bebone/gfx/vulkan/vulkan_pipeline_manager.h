#ifndef BEBONE_VULKAN_PIPELINE_MANAGER_H
#define BEBONE_VULKAN_PIPELINE_MANAGER_H

#include "../gfx_backend.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_pipeline_tuples.h"

namespace bebone::gfx::vulkan {
    class VulkanConstRange;

    class VulkanPipelineManager : public VulkanApi, private core::NonCopyable {
        private:
            std::shared_ptr<VulkanDescriptorPool> descriptor_pool;
            std::vector<std::shared_ptr<VulkanDescriptorSetLayout>> descriptor_layouts;

        public:
            VulkanPipelineManager(VulkanDevice& device);

            VulkanManagedPipelineTuple create_pipeline(
                std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<VulkanSwapChain>& swapChain,
                const std::string& vertex_shader_file_path,
                const std::string& fragment_shader_file_path,
                const std::vector<VulkanConstRange>& constantRanges,
                const std::vector<VulkanDescriptorSetLayoutBinding>& bindings,
                VulkanPipelineConfig configInfo
            );

            void destroy(VulkanDevice& device) override;
    };
}

#endif
