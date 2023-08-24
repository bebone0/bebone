#pragma once

#include "device_impl.h"

// vulkan headers
#include <vulkan/vulkan.h>

// std lib headers
#include <string>
#include <vector>

class MyEngineSwapChainImpl {
	public:
		const size_t FIF;

		MyEngineSwapChainImpl(DeviceImpl &deviceRef, VkExtent2D windowExtent, const size_t& fif);
		~MyEngineSwapChainImpl();

		MyEngineSwapChainImpl(const MyEngineSwapChainImpl &) = delete;
		void operator=(const MyEngineSwapChainImpl &) = delete;

		VkFramebuffer getFrameBuffer(int index) { return swapChainFramebuffers[index]; }
		VkRenderPass getRenderPass() { return renderPass; }
		VkImageView getImageView(int index) { return swapChainImageViews[index]; }
		size_t imageCount() { return swapChainImages.size(); }
		VkFormat getSwapChainImageFormat() { return swapChainImageFormat; }
		VkExtent2D getSwapChainExtent() { return swapChainExtent; }
		uint32_t width() { return swapChainExtent.width; }
		uint32_t height() { return swapChainExtent.height; }

		float extentAspectRatio() {
			return static_cast<float>(swapChainExtent.width) / static_cast<float>(swapChainExtent.height);
		}
		
		VkFormat findDepthFormat();

		VkResult acquireNextImage(uint32_t *imageIndex);
		VkResult submitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex);

		size_t currentFrame = 0;
  	private:
		void createSwapChain();
		void createImageViews();
		void createDepthResources();
		void createRenderPass();
		void createFramebuffers();
		void createSyncObjects();

		// Helper functions
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;

		std::vector<VkFramebuffer> swapChainFramebuffers;
		VkRenderPass renderPass;

		std::vector<VkImage> depthImages;
		std::vector<VkDeviceMemory> depthImageMemorys;
		std::vector<VkImageView> depthImageViews;
		
		std::vector<VkImage> swapChainImages;
		std::vector<VkImageView> swapChainImageViews;

		DeviceImpl &device;
		VkExtent2D windowExtent;

		VkSwapchainKHR swapChain;

		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		std::vector<VkFence> imagesInFlight;
};
