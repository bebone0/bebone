#ifndef _BEBONE_GFX_UNIFORM_BUFFER_H_
#define _BEBONE_GFX_UNIFORM_BUFFER_H_

#include <memory>

#include "uniform_buffer_handle.h"

#include "vulkan/vulkan_command_buffer.h"
#include "vulkan/vulkan_uniform_buffer_impl.h"

namespace bebone::gfx {
    template<class DataType>
    class UniformBuffer {
        private:
            std::vector<VulkanUniformBufferImpl*> _impl; 

        public:
            UniformBuffer(std::vector<VulkanUniformBufferImpl*> impl) : _impl(impl) {

            }

            ~UniformBuffer() {
                for(const auto& buf : _impl) {
                    delete buf;
                }

                _impl.clear();
            }

            void set_data(const VulkanFrame& frame, const DataType& data) {
                _impl[frame.frameIndex]->set_data(data);
            }

            VulkanUniformBufferImpl* get_impl(const size_t index) {
                return _impl[index];
            }
    
            const UniformBufferHandle& get_handle(const size_t& index) const {
                return _impl[index]->get_handle();
            }

            size_t get_impl_size() const {
                return _impl.size();
            }
    };
}

#endif
