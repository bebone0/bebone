file(GLOB_RECURSE BEBONE_GFX_SRC_FILES "*.cpp")

set(BEBONE_GFX_INCLUDES "${CMAKE_SOURCE_DIR}/src/bebone/gfx")

find_package(Vulkan REQUIRED COMPONENTS glslang SPIRV-Tools)

list(APPEND BEBONE_GFX_INCLUDES 
    "${PROJECT_SOURCE_DIR}/3dparty/glad/include"
    "${PROJECT_SOURCE_DIR}/3dparty/stb"
    "${PROJECT_SOURCE_DIR}/3dparty/glfw/include"
    ${Vulkan_INCLUDE_DIRS}
)

set(BEBONE_GFX_LIBRARIES
    glfw
    stb_image
    stb_truetype
    glad
    Vulkan::Vulkan
    Vulkan::glslang
    Vulkan::SPIRV-Tools
)

set(BEBONE_GFX_INCLUDES "${BEBONE_GFX_INCLUDES}" CACHE INTERNAL "")
include_directories(${BEBONE_GFX_INCLUDES})

add_library(bebone_gfx STATIC ${BEBONE_GFX_SRC_FILES})
target_link_libraries(bebone_gfx PUBLIC ${BEBONE_GFX_LIBRARIES})
