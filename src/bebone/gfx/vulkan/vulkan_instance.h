#ifndef _BEBONE_GFX_VULKAN_INSTANCE_H_
#define _BEBONE_GFX_VULKAN_INSTANCE_H_

#include <memory>
#include <unordered_set>

#include "../gfx_backend.h"
#include "../window/vulkan_window.h"
#include "vulkan_debug_messenger.h"

#include "interface/i_vulkan_instance.h"

namespace bebone::gfx {
    class VulkanInstance : public IVulkanInstance, private core::NonCopyable {
        private:
            VkInstance instance;

            std::unique_ptr<VulkanDebugMessenger> debug_messenger;

            bool check_validation_layer_support();
            static void has_gflw_required_instance_extensions();
            static std::vector<const char *> get_required_extensions();

            bool const static enable_validation_layers = true;

        public:
            VulkanInstance();
            ~VulkanInstance() override;

            const std::vector<const char *> validation_layers = { "VK_LAYER_KHRONOS_validation" };

            // Vulkan Instance
            [[nodiscard]] VkInstance get_vk_instance() const override;
    };
}

#endif
