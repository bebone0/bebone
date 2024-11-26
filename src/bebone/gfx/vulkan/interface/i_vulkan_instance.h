#ifndef _BEBONE_GFX_I_VULKAN_INSTANCE_H_
#define _BEBONE_GFX_I_VULKAN_INSTANCE_H_

#include "../../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class IVulkanInstance {
        public:
            virtual ~IVulkanInstance() = default;

            [[nodiscard]] virtual VkInstance get_vk_instance() const = 0;
    };
}

#endif