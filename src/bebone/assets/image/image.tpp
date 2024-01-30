#ifndef _BEBONE_ASSETS_IMAGE_TPP_
#define _BEBONE_ASSETS_IMAGE_TPP_

#include <vector>
#include <memory>

#include <iostream>

#include "../../core/types.h"
#include "../../core/noncopyable.h"

#include <stb_image.h>

namespace bebone::assets {
    using namespace bebone::core;

    template<typename _Color>
    class Image : public NonCopyable {
        private:
            std::vector<_Color> color;

            int width;
            int height;
            int channels;

        public:
            Image(const std::vector<_Color>& data, const size_t& width, const size_t& height, const size_t& channels)
                : width(width),
                  height(height),
                  channels(channels)
            {
                color = data;
            }

            void* data() {
                return color.data();
            }

            const int& get_width() const {
                return width;
            }

            const int& get_height() const {
                return height;
            }

            const int& get_channels() const {
                return channels;
            }

            static std::shared_ptr<Image<_Color>> load_from_file(const std::string& filePath) {
                int width, height, channels;
                void* bytes = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

                const auto size = width * height;

                if(channels == 3) {
                    auto* b = static_cast<ColorRGB24*>(bytes);

                    std::vector<_Color> color(size);

                    for(auto i = 0; i < size; ++i)
                        color[i] = b[i].to<_Color>();

                    stbi_image_free(bytes);

                    return std::make_shared<Image>(color, width, height, channels);
                } else if(channels == 4) {
                    auto* b = static_cast<ColorRGBA32*>(bytes);

                    std::vector<_Color> color(size);

                    for(auto i = 0; i < size; ++i)
                        color[i] = b[i].to<_Color>();

                    stbi_image_free(bytes);

                    return std::make_shared<Image>(color, width, height, channels);
                }

                throw std::runtime_error("Unsupported color format " + filePath);
            }
    };
}

#endif