#ifndef _BEBONE_RENDERER_IMESH_BUILDER_H_
#define _BEBONE_RENDERER_IMESH_BUILDER_H_

#include "renderer_backend.h"

#include "imesh.h"

namespace bebone::renderer {
    template<class VertexType>
    class IMeshBuilder {
        public:
            using VertexTriangle = VertexType[3];

            virtual ~IMeshBuilder() = default;

            virtual void append_triangle(const VertexTriangle& triangle) = 0;
            virtual void append_triangles(const VertexTriangle* triangles, const u64& count) = 0;

            virtual void append_vertex(const VertexType& vertex) = 0;
            virtual void append_vertices(const VertexType* vertices, const u64& count) = 0;

            virtual void append_raw(const VertexType* vertices, const u64& vert_count, const u32* indices , const u64& ind_count) = 0;

            virtual void reset() = 0;

            virtual std::shared_ptr<IMesh> build() = 0;
    };
}

#endif