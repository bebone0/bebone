#ifndef _BEBONE_RENDERER_VULKAN_RENDERER_H_
#define _BEBONE_RENDERER_VULKAN_RENDERER_H_

#include "../irenderer.h"
#include "../irender_graph.h"
#include "vulkan_render_graph_impl.h"
#include "vulkan_triangle_mesh.h"
#include "vulkan_triangle_mesh_builder.h"
#include "../pbr_render_graph.h"
#include "vulkan_texture.h"
#include "vulkan_program_manager.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanRenderer : public IRenderer {
        private:
            std::shared_ptr<Window> window;

            std::shared_ptr<VulkanInstance> instance;
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanSwapChain> swap_chain;

            std::vector<std::shared_ptr<IModel>> model_pool;

            std::shared_ptr<VulkanProgramManager> program_manager;

            std::shared_ptr<IRenderGraph> render_graph;

            std::shared_ptr<ICamera> camera;

        protected:
            void resize_viewport(const Vec2i& new_size) override;

        public:
            VulkanRenderer(std::shared_ptr<gfx::Window>& window);
            ~VulkanRenderer() override;

            std::shared_ptr<IMaterial> create_material(const std::string& albedo) override;
            std::shared_ptr<ITexture> load_texture(const std::string& file_path) override;

            std::shared_ptr<IMesh> load_mesh(const std::string& file_path) override;
            std::shared_ptr<IMesh> create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) override;

            ModelHandle create_model(std::shared_ptr<IMesh>& mesh, std::shared_ptr<IMaterial>& material) override;

            void render(const ModelHandle& handle, const Transform& transform = {}) override;

            void present() override;

            std::shared_ptr<IRenderGraphImpl> create_render_graph_impl() override;
    };
}

#endif
