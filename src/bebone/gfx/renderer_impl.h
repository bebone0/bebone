#ifndef _BEBONE_GFX_RENDERER_IMPLEMENTATION_H_
#define _BEBONE_GFX_RENDERER_IMPLEMENTATION_H_

#include <memory>

#include "gfx_backend.h"

#include "buffer_impl.h"
#include "command_buffer.h"
#include "command_buffer_pool.h"

#include "uniform_buffer.h"

#include "descriptor_pool.h"
#include "pipeline_layout_builder.h"

namespace bebone::gfx {
    class RendererImpl {
        private:

        public:
            virtual ~RendererImpl() {}

            virtual CommandBuffer& get_command_buffer() = 0;
            virtual CommandBufferPool& get_command_buffer_pool() = 0;
            virtual DescriptorPool& get_descriptor_pool() = 0;

            virtual Pipeline create_pipeline(PipelineLayout& pipelineLayout, const std::vector<unsigned int>& vertexSpirvCode, const std::vector<unsigned int>& fragmentSpirvCode) = 0;
            
            virtual VertexBuffer create_vertex_buffer(const std::vector<Vertex>&) = 0;
            virtual IndexBuffer create_index_buffer(const std::vector<int>&) = 0;
            virtual UniformBuffer create_uniform_buffer(const size_t& size) = 0;
            virtual PipelineLayoutBuilder create_pipeline_layout_builder() = 0;

            virtual std::shared_ptr<MyEngineSwapChainImpl> get_swap_chain() = 0;

            virtual void present() = 0;
    };
}
#endif
