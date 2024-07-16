#ifndef _BEBONE_RENDERER_IRENDERER_H_
#define _BEBONE_RENDERER_IRENDERER_H_

#include "renderer_backend.h"

#include "irender_graph.h"
#include "ipass.h"

#include "itexture.h"
#include "imaterial.h"

#include "imesh.h"
#include "imesh_builder.h"
#include "imesh_generator.h"
#include "imesh_loader.h"
#include "obj_mesh_loader.h"

#include "vertex.h"
#include "transform.h"

#include "pbr_render_graph.h"
#include "pbr_material.h"

namespace bebone::renderer {
    struct MeshHandle { size_t index; };
    struct ModelHandle { size_t index; };

    class IRenderer {
        private:
            const GfxAPI api;

        protected:
            virtual void resize_viewport(const Vec2i& new_size) = 0;

            std::shared_ptr<IRenderGraph> create_default_render_graph(const Vec2i& viewport);

        public:
            IRenderer(const GfxAPI& api);
            virtual ~IRenderer() = default;

            virtual std::shared_ptr<IMaterial> create_material(const std::string& albedo) = 0;
            virtual std::shared_ptr<ITexture> load_texture(const std::string& file_path) = 0;

            virtual std::shared_ptr<IMesh> load_mesh(const std::string& file_path) = 0;
            virtual std::shared_ptr<IMesh> create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) = 0;

            virtual ModelHandle create_model(std::shared_ptr<IMesh>& mesh, std::shared_ptr<IMaterial>& material) = 0;

            virtual void render(const ModelHandle& handle, const Transform& transform) = 0;

            virtual void present() = 0;

            virtual std::shared_ptr<IRenderGraphImpl> create_render_graph_impl() = 0;
            std::shared_ptr<IRenderGraph> create_render_graph(const std::string& name);

            const GfxAPI& get_api() const;
    };
}

#endif
