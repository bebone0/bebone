#define BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
#define BEBONE_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

using namespace bebone::core;
using namespace bebone::gfx;
using namespace bebone::gfx::vulkan;

struct Vertex { Vec3f pos, color; };
struct Handles { u32 cameraHandle, transformHandle; };
struct CameraTransform { Mat4f view, proj; };
struct Transform { Mat4f transform, scale, rotation; };

const std::vector<Vertex> vertices = {
    {{-1.0, -1.0, -1.0}, {0.0f, 1.0f, 1.0f}},
    {{ 1.0, -1.0, -1.0}, {0.0f, 1.0f, 0.0f}},
    {{ 1.0,  1.0, -1.0}, {0.0f, 0.0f, 1.0f}},
    {{-1.0,  1.0, -1.0}, {0.0f, 0.0f, 0.0f}},
    {{-1.0, -1.0,  1.0}, {1.0f, 1.0f, 1.0f}},
    {{ 1.0, -1.0,  1.0}, {1.0f, 1.0f, 0.0f}},
    {{ 1.0,  1.0,  1.0}, {1.0f, 0.0f, 1.0f}},
    {{-1.0,  1.0,  1.0}, {1.0f, 0.0f, 0.0f}},
};

// Todo make this nicer
const auto vertexDescriptions = VulkanPipelineVertexInputStateTuple {
    .binding_descriptions = {
        { 0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX }
    },
    .attribute_descriptions = {
        { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos) },
        { 1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, color) },
    }
};

const std::vector<int> indices = {
    0, 1, 2, 2, 3, 0,
    1, 5, 6, 6, 2, 1,
    7, 6, 5, 5, 4, 7,
    4, 0, 3, 3, 7, 4,
    4, 5, 1, 1, 0, 4,
    3, 2, 6, 6, 7, 3
};

int main() {
    GLFWContext::init();

    auto window = WindowFactory::create_window("2. Vulkan 3d cube example", 800, 600, GfxAPI::Vulkan);

    auto instance = VulkanInstance::create_instance();
    auto device = instance->create_device(window);
    auto swapChain = device->create_swap_chain(window);

    auto pipeline_manager = device->create_pipeline_manager();

    auto pipeline = pipeline_manager->create_pipeline(
        device, swapChain, "vert.glsl", "frag.glsl",
        { VulkanConstRange::common(sizeof(Handles), 0) },
        { {BindlessUniform, 0}, {BindlessUniform, 1} },
        { .vertex_input_state = { .vertex_descriptions = vertexDescriptions } }
    );

    auto vb = device->create_buffer_memory_from(vertices);
    auto eb = device->create_buffer_memory_from(indices);

    auto transformUBO = device->create_buffer_memorys(sizeof(Transform), 3);
    auto cameraUBO = device->create_buffer_memorys(sizeof(CameraTransform), 3);

    auto t_handles = pipeline.bind_uniform_buffer(device, transformUBO, 0);
    auto c_handles = pipeline.bind_uniform_buffer(device, cameraUBO, 1);

    auto commandBufferPool = device->create_command_buffer_pool();
    auto commandBuffers = commandBufferPool->create_command_buffers(device, 3);

    auto cameraTransform = CameraTransform {
        Mat4f::view(Vec3f(0.0f, 0.0f, 10.0f), Vec3f::back, Vec3f::down),
        Mat4f::perspective(1.0472, window->get_aspect(), 0.1f, 100.0f)
    };

    for(auto& ubo : cameraUBO)
        ubo.upload_data(device, &cameraTransform, sizeof(CameraTransform));

    auto transform = Transform {
        Mat4f::translation(Vec3f::zero),
        Mat4f::scale(1.0f),
        Mat4f::identity()
    };

    f32 t = 0.0f;
    while (!window->closing()) {
        GLFWContext::poll_events();

        uint32_t frame;
        if(!swapChain->acquire_next_image(device, &frame).is_ok())
            continue;

        transform.rotation = trait_bryan_angle_yxz(Vec3f(t * 0.001f, (t++) * 0.001f, 0.0f));
        transformUBO[frame].upload_data(device, &transform, sizeof(Transform));

        auto handles = Handles {
            static_cast<u32>(c_handles[frame]),
            static_cast<u32>(t_handles[frame])
        };

        auto& cmd = *commandBuffers[frame];

        cmd.begin_record();
        cmd.begin_render_pass(swapChain, frame);
        cmd.set_viewport(0, 0, window->get_width(), window->get_height());
        cmd.bind_managed_pipeline(pipeline, frame);
        cmd.push_constant(pipeline.layout, sizeof(Handles), 0, &handles);
        cmd.bind_vertex_buffer(vb);
        cmd.bind_index_buffer(eb);
        cmd.draw_indexed(indices.size());
        cmd.end_render_pass();
        cmd.end_record();

        if(!swapChain->submit_command_buffers(device, commandBuffers[frame], &frame).is_ok()) // Todo check if window is resized
            continue;
    }

    instance->destroy();

    GLFWContext::terminate();

    return 0;
}