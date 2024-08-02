#ifndef _BEBONE_RENDERER_IMESH_BUILDER_H_
#define _BEBONE_RENDERER_IMESH_BUILDER_H_

#include "renderer_backend.h"

#include "imesh.h"
#include "../vertex.h"

namespace bebone::renderer {
    class IMeshBuilder {
        public:
            using VertexTriangle = Vertex[3];

            virtual ~IMeshBuilder() = default;

            virtual void append_triangle(const VertexTriangle& triangle) = 0;
            virtual void append_triangles(const VertexTriangle* triangles, const u64& count) = 0;

            virtual void append_vertex(const Vertex& vertex) = 0;
            virtual void append_vertices(const Vertex* vertices, const u64& count) = 0;

            virtual void append_raw(const Vertex* vertices, const u64& vert_count, const u32* indices , const u64& ind_count) = 0;

            virtual void reset() = 0;

            virtual std::shared_ptr<IMesh> build() = 0;
    };
}

#endif