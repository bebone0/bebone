#ifndef _BEBONE_GFX_SWAP_CHAIN_IMPL_H_
#define _BEBONE_GFX_SWAP_CHAIN_IMPL_H_

#include "vulkan/vulkan_device.h"

#include <string>
#include <vector>

#include "render_target.h"

using namespace bebone::gfx;

class MyEngineSwapChainImpl {
	private:
		void createSwapChain();
		void createRenderTarget();
		void createSyncObjects();

		// Helper functions
		static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
		static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
		static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, VkExtent2D windowExtent);

		VulkanDevice &device;
		
		VkExtent2D extent;
		VkSurfaceFormatKHR surfaceFormat;
		VkPresentModeKHR presentMode;

		VkSwapchainKHR swapChain;

		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		std::vector<VkFence> imagesInFlight;
	public:
		void recreate(VkExtent2D windowExtent);

		std::unique_ptr<RenderTarget> renderTarget;
		
		const size_t FIF;

		MyEngineSwapChainImpl(VulkanDevice &deviceRef, VkExtent2D windowExtent, const size_t& fif);
		~MyEngineSwapChainImpl();

		MyEngineSwapChainImpl(const MyEngineSwapChainImpl &) = delete;
		void operator=(const MyEngineSwapChainImpl &) = delete; 

		VkResult acquireNextImage(uint32_t *imageIndex);
		VkResult submitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex);

		size_t currentFrame = 0;
};

#endif