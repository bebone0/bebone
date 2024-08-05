#ifndef _BEBONE_RENDERER_IMESH_H_
#define _BEBONE_RENDERER_IMESH_H_

#include "renderer_backend.h"
#include "vertex.h"

namespace bebone::renderer {
        enum class MeshHandle : u32 { Invalid = 0 };

        class ICommandEncoder;

        class IMesh {
            public:
                virtual ~IMesh() = default;

                // Todo, resolve this command encoder cringe
                virtual void bind(ICommandEncoder* encoder) = 0;

                virtual u64 triangle_count() const = 0;
                virtual u64 vertex_count() const = 0;
        };
}

#endif
