#include "bebone/bebone.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

void window_resize_event_listener(WindowSizeEvent& event) {
    std::cout << "Window resize event !\n";
}

struct WindowPosEventListener : EventListener<WindowPosEvent> {
    void operator()(WindowPosEvent& event) {
        std::cout << "Window pos event !\n";
    }
};

int main() {
    glfwInit();

    auto window = WindowFactory::create_window("0. OpenGL window example", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

    WindowPosEventListener listener;
    window->EventDispatcher<WindowEvent>::add_listener(listener);
    window->EventDispatcher<WindowEvent>::add_listener(window_resize_event_listener);
    window->EventDispatcher<WindowEvent>::add_listener([](WindowFocusEvent& event) {
        std::cout << "Window focus event !\n";
    });

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window->get_backend());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
