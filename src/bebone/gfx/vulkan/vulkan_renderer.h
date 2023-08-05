#ifndef _BEBONE_GFX_VULKAN_RENDERER_H_
#define _BEBONE_GFX_VULKAN_RENDERER_H_

#include <memory>

#include "../gfx_backend.h"
#include "../renderer.h"

#include "vulkan_command_buffer_pool.h"
#include "vulkan_command_buffer.h"

namespace bebone::gfx {
    class VulkanRenderer : public Renderer {
        private:
            std::unique_ptr<VulkanCommandBufferPool> commandBuffers;

        public:
            VulkanRenderer() {
                commandBuffers = std::make_unique<VulkanCommandBufferPool>(2);
            }

            ~VulkanRenderer() {
                
            }

            CommandBuffer& get_command_buffer() override {
                return commandBuffers->get_command_buffer(1);
            }
    };
}
#endif
