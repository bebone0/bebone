#include <vector>

#define BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
#define BEBONE_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

using namespace bebone;
using namespace bebone::gfx;
using namespace bebone::renderer;
using namespace bebone::gfx::opengl;

class CubeMeshGenerator : public IMeshGenerator {
    public:
        CubeMeshGenerator(const std::shared_ptr<IMeshBuilder>& builder) : IMeshGenerator(builder) {

        }

        void reset() override {

        }

        std::shared_ptr<IMesh> generate() override {
            const vector<Vertex> vertices {
                {{-1.0, -1.0,  1.0},   {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
                {{ 1.0, -1.0,  1.0},   {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
                {{ 1.0,  1.0,  1.0},   {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
                {{-1.0,  1.0,  1.0},   {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
                {{-1.0, -1.0, -1.0},   {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
                {{ 1.0, -1.0, -1.0},   {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
                {{ 1.0,  1.0, -1.0},   {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
                {{-1.0,  1.0, -1.0},   {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}
            };

            const vector<u32> indices {
                0, 1, 2, 2, 3, 0,
                1, 5, 6, 6, 2, 1,
                7, 6, 5, 5, 4, 7,
                4, 0, 3, 3, 7, 4,
                4, 5, 1, 1, 0, 4,
                3, 2, 6, 6, 7, 3
            };

            return std::make_shared<OpenGLTriangleMesh>(vertices, indices);
        }
};

class QuadMeshGenerator : public IMeshGenerator {
    public:
        QuadMeshGenerator(const std::shared_ptr<IMeshBuilder>& builder) : IMeshGenerator(builder) {

        }

        void reset() override {

        }

        std::shared_ptr<IMesh> generate() override {
            const std::vector<Vertex> vertices {
                {{1.0f,  1.0f, 0.0f},    {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}},
                {{1.0f, -1.0f, 0.0f},    {0.0f, 1.0f, 0.0f},   {1.0f, 0.0f}},
                {{-1.0f, -1.0f,0.0f},   {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f}},
                {{-1.0f,  1.0f,0.0f},   {1.0f, 1.0f, 0.0f},   {0.0f, 1.0f}}
            };

            const std::vector<u32> indices {
                0, 1, 3,
                1, 2, 3
            };

            return std::make_shared<OpenGLTriangleMesh>(vertices, indices);
        }
};

int main() {
    glfwInit();

    auto window = WindowFactory::create_window("7. OpenGL bloom example", 800, 600, GfxAPI::OpenGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, 800, 600);

    GLShaderProgram geometry_program(
        GLShaderFactory::create_shader("main.vert.glsl", ShaderTypes::vertex_shader, EnableUniforms),
        GLShaderFactory::create_shader("main.frag.glsl", ShaderTypes::fragment_shader, EnableUniforms));

    GLShaderProgram blur_program(
        GLShaderFactory::create_shader("blur.vert.glsl", ShaderTypes::vertex_shader, EnableUniforms),
        GLShaderFactory::create_shader("blur.frag.glsl", ShaderTypes::fragment_shader, EnableUniforms));

    GLShaderProgram post_program(
            GLShaderFactory::create_shader("post.vert.glsl", ShaderTypes::vertex_shader, EnableUniforms),
            GLShaderFactory::create_shader("post.frag.glsl", ShaderTypes::fragment_shader, EnableUniforms));

    GLContext::enable(GL_DEPTH_TEST);

    auto transform = renderer::Transform {};
    auto camera = Mat4f::translation(Vec3f(0, 0, 5)) * Mat4f::perspective(1, window->get_aspect(), 0.1f, 100.0f);

    auto cube_generator = std::make_shared<CubeMeshGenerator>(std::make_shared<OpenGLTriangleMeshBuilder>());
    auto cube_mesh = cube_generator->generate();

    auto quad_generator = std::make_shared<QuadMeshGenerator>(std::make_shared<OpenGLTriangleMeshBuilder>());
    auto quad_mesh = quad_generator->generate();

    // Geometry pass
    auto geometry_fbo = GLFramebuffer();
        auto geometry_texture = GLTexture2D(800, 600);
        auto grayscale_texture = GLTexture2D(800, 600);
        auto geometry_renderbuffer = GLRenderbuffer();
        geometry_renderbuffer.storage(GL_DEPTH24_STENCIL8, 800, 600);

        geometry_fbo.attach_texture_2d(GL_COLOR_ATTACHMENT0, geometry_texture);
        geometry_fbo.attach_texture_2d(GL_COLOR_ATTACHMENT1, grayscale_texture);
        geometry_fbo.attach_renderbuffer(GL_DEPTH_STENCIL_ATTACHMENT, geometry_renderbuffer);

    // Blur pass
    auto blur_fbo = GLFramebuffer();
        auto blur_texture = GLTexture2D(800, 600);
        auto blur_renderbuffer = GLRenderbuffer();
        blur_renderbuffer.storage(GL_DEPTH24_STENCIL8, 800, 600);

        blur_fbo.attach_texture_2d(GL_COLOR_ATTACHMENT0, blur_texture);
        blur_fbo.attach_renderbuffer(GL_DEPTH_STENCIL_ATTACHMENT, blur_renderbuffer);

    while (!window->closing()) {
        transform.rotation.x += 0.02f;
        transform.rotation.z -= 0.02f;

        // Geometry pass
        geometry_fbo.bind();
            GLenum drawBuffers[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
            glDrawBuffers(2, drawBuffers); // Todo, this needs to be abstracted

            GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
            GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            geometry_program.enable();
            geometry_program.set_uniform("transform", transform.final_matrix());
            geometry_program.set_uniform("cam", camera);

            cube_mesh->bind();
            GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(cube_mesh->triangle_count()), GL_UNSIGNED_INT, nullptr);
        geometry_fbo.unbind();

        // Blur pass
        blur_fbo.bind();
            GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
            GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            blur_program.enable();
            geometry_texture.bind();

            quad_mesh->bind();
            GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(quad_mesh->triangle_count()), GL_UNSIGNED_INT, nullptr);
        blur_fbo.unbind();

        // Final pass
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        post_program.enable();
        quad_mesh->bind();

        grayscale_texture.bind_texture_unit(0);
        blur_texture.bind_texture_unit(1);
        GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(quad_mesh->triangle_count()), GL_UNSIGNED_INT, nullptr);

        GLFWContext::swap_buffers(*window);
        GLFWContext::poll_events();
    }

    geometry_program.destroy();

    GLFWContext::terminate();

    return 0;
}