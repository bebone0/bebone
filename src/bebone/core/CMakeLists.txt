set(BEBONE_CORE_INCLUDES
    "${PROJECT_SOURCE_DIR}/src/bebone/core"
    "${PROJECT_SOURCE_DIR}/3dparty/glad/include"
    "${PROJECT_SOURCE_DIR}/3dparty/glfw/include"
    "${PROJECT_SOURCE_DIR}/3dparty/Vulkan-Headers/include"
)

set(BEBONE_CORE_INCLUDES "${BEBONE_CORE_INCLUDES}" CACHE INTERNAL "")
include_directories(${BEBONE_CORE_INCLUDES})

file(GLOB_RECURSE BEBONE_CORE_SRC_FILES "*.cpp")
add_library(bebone_core STATIC ${BEBONE_CORE_SRC_FILES})
