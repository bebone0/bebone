file(GLOB_RECURSE BEBONE_ASSETS_SRC_FILES "*.cpp")

include_directories(
    "${PROJECT_SOURCE_DIR}/3dparty/stb"
)

add_library(bebone_assets STATIC ${BEBONE_ASSETS_SRC_FILES})

target_link_libraries(bebone_assets stb_image)
target_link_libraries(bebone_assets stb_image_write)
target_link_libraries(bebone_assets stb_truetype)
