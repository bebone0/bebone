#ifndef _BEBONE_RENDERER_IRENDER_GRAPH_H_
#define _BEBONE_RENDERER_IRENDER_GRAPH_H_

#include "irender_graph_impl.h"

namespace bebone::renderer {
    class IRenderer;
    class GLRenderer;
    class VulkanRenderer;

    class IRenderGraph {
        private:
            std::string name;
            std::unique_ptr<IRenderGraphImpl> impl;

        protected:
            IRenderGraph(const std::string& name, std::unique_ptr<IRenderGraphImpl> impl);

        public:
            friend class IRenderer;
            friend class GLRenderer;
            friend class VulkanRenderer;

            virtual ~IRenderGraph() = default;

            virtual void assemble();

            virtual void record();
            virtual void submit();
            virtual void reset();

            void add_pass(const std::shared_ptr<IPass>& render_pass);
            std::optional<std::shared_ptr<IPass>> get_render_pass(const std::string& pass_name) const;
            std::vector<std::shared_ptr<IPass>>& get_render_passes();

            void add_resource(const std::shared_ptr<IResource>& render_resource);
            std::optional<std::shared_ptr<IResource>> get_render_resource(const std::string& resource_name) const;
            std::vector<std::shared_ptr<IResource>>& get_render_resources();

            virtual std::shared_ptr<IPassFactory> create_pass_factory() const;
            virtual std::shared_ptr<IResourceFactory> create_resource_factory() const;
    };
}

#endif
