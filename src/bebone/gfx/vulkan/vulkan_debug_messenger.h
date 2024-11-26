#ifndef _BEBONE_GFX_VULKAN_DEBUG_MESSENGER_H_
#define _BEBONE_GFX_VULKAN_DEBUG_MESSENGER_H_

#include "../gfx_backend.h"
#include "interface/i_vulkan_instance.h"

namespace bebone::gfx {
    class IVulkanInstance;

    class VulkanDebugMessenger : private core::NonCopyable {
        private:
            IVulkanInstance& instance_owner;

        private:
            VkDebugUtilsMessengerEXT debug_messenger;

        public:
            VulkanDebugMessenger(IVulkanInstance& instance);
            ~VulkanDebugMessenger();

            static void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT &create_info);
    };
}


#endif
