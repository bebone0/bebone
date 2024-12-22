file(GLOB_RECURSE BEBONE_RENDERER_SRC_FILES "*.cpp")

set(BEBONE_RENDERER_INCLUDES "${CMAKE_SOURCE_DIR}/src/bebone/renderer" )

list(APPEND BEBONE_RENDERER_INCLUDES
    "${PROJECT_SOURCE_DIR}/3dparty/glad/include"
    "${PROJECT_SOURCE_DIR}/3dparty/glfw/include"
    "${PROJECT_SOURCE_DIR}/3dparty/Vulkan-Headers/include"
    "${PROJECT_SOURCE_DIR}/3dparty/stb"
    "${PROJECT_SOURCE_DIR}/3dparty/glfw/include"
    "${PROJECT_SOURCE_DIR}/3dparty/imgui"
)

find_package(vulkan REQUIRED)

set(BEBONE_RENDERER_LIBRARIES
    glfw
    stb_image
    glad
    glslang
    SPIRV
    glslang-default-resource-limits
    ${Vulkan_LIBRARIES}
    imgui
    bebone_core
    bebone_assets
    bebone_gfx
)

set(BEBONE_RENDERER_INCLUDES "${BEBONE_RENDERER_INCLUDES}" CACHE INTERNAL "")
include_directories(${BEBONE_RENDERER_INCLUDES})

add_library(bebone_renderer STATIC ${BEBONE_RENDERER_SRC_FILES})
target_link_libraries(bebone_renderer ${BEBONE_RENDERER_LIBRARIES})
