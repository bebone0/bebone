#ifndef _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_H_
#define _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_H_

#include <stdexcept>

#include "../command_buffer.h"
#include "../../core/arena_container.h"

namespace bebone::gfx {
    class VulkanCommandBuffer : public CommandBuffer {
        private:
            core::ArenaContainer arena;
        protected:

        public:
            VulkanCommandBuffer();

            void begin_record() override;
            void end_record() override;

            void begin_render_pass(MyEngineSwapChain& swapChain, int frameBuffer) override;
            void end_render_pass() override;

            void bind_pipeline(std::shared_ptr<Pipeline>& pipeline) override;
            void bind_buffer(std::shared_ptr<VertexBuffer>& model) override;
            void draw(const size_t& vertexCount) override;

            void preprocess() override;
            void submit() override;

            VkCommandBuffer commandBuffer;

            RenderingApi get_api() override;
    };  
}

#endif