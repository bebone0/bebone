#ifndef _BEBONE_RENDERER_IMESH_H_
#define _BEBONE_RENDERER_IMESH_H_

#include "imesh_impl.h"

namespace bebone::renderer {
    class ICommandEncoder;

    class IMesh {
        protected:
            std::shared_ptr<IMeshImpl> impl;

        public:
            IMesh(const std::shared_ptr<IMeshImpl>& impl);

            // Todo, resolve this command encoder cringe
            virtual void bind(ICommandEncoder* encoder);

            virtual u64 triangle_count() const;
            virtual u64 vertex_count() const;

            std::shared_ptr<IMeshImpl> get_impl() const;
    };
}

#endif
