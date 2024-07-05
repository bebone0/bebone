#ifndef _BEBONE_RENDERER_IMESH_LOADER_H_
#define _BEBONE_RENDERER_IMESH_LOADER_H_

#include <fstream>

#include "../renderer_backend.h"
#include "imesh_builder.h"

namespace bebone::renderer {
    class IMeshLoader {
        protected:
            std::shared_ptr<IMeshBuilder> builder;

        public:
            IMeshLoader(const std::shared_ptr<IMeshBuilder>& builder);
            virtual ~IMeshLoader() = default;

            virtual void reset() = 0;

            virtual std::shared_ptr<IMesh> load_from_file(const std::string& file) = 0;
    };

}

#endif