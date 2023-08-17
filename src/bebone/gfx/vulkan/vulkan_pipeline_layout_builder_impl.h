#ifndef _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_BUILDER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_BUILDER_IMPLEMENTATION_H_

#include <cassert>

#include "../device_impl.h"

#include "../pipeline_layout_builder_impl.h"

#include "vulkan_descriptor_pool.h"
#include "vulkan_pipeline_layout_impl.h"
#include "vulkan_uniform_buffer_impl.h"

namespace bebone::gfx {
    struct VulkanDescripotSetLayoutBlueprint {
        size_t binding;
        VkDescriptorType type;
        std::vector<BufferImpl*> buffers;
    };

    class VulkanPipelineLayoutBuilderImpl : public PipelineLayoutBuilderImpl {
        private:
            DeviceImpl& _device;
            const size_t _fif;
            std::vector<VulkanDescripotSetLayoutBlueprint> descriptorsSetBlueprints;

        public:
            VulkanPipelineLayoutBuilderImpl(const size_t& fif, DeviceImpl& device) : _device(device), _fif(fif) {
            }

            ~VulkanPipelineLayoutBuilderImpl() {

            }

            void bind_uniform_buffer(const size_t& binding, UniformBuffer& buffer) override {
                std::vector<BufferImpl*> buffers;

                for(size_t i = 0; i < buffer.get_impl_size(); ++i) {
                    buffers.push_back(buffer.get_impl(i));
                }

                descriptorsSetBlueprints.push_back({binding, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, buffers});
            }

            PipelineLayout build() override {
                std::shared_ptr<VulkanDescriptorPool> _descriptorPool = std::make_shared<VulkanDescriptorPool>(_device, 2);

                for(auto& descriptorsSetBlueprint : descriptorsSetBlueprints) {
                    VkDescriptorSetLayout* descriptorSetLayout = _descriptorPool->create_descriptor_set_layout(descriptorsSetBlueprint.binding, descriptorsSetBlueprint.type);

                    for(auto& buf : descriptorsSetBlueprint.buffers) {
                        VulkanUniformBufferImpl* vulkanBufImpl = static_cast<VulkanUniformBufferImpl*>(buf);
                        VkDescriptorSet* descriptorSet = _descriptorPool->create_descriptor(descriptorSetLayout, vulkanBufImpl->get_buffer());
                        vulkanBufImpl->bind_descriptor_set(descriptorSet);
                    }
                }
                
                return PipelineLayout::create_from_impl<VulkanPipelineLayoutImpl>(_device, _descriptorPool);
            }
    };
}

#endif