#include <iostream>
#include <thread>

#include "bebone/bebone.h"

using namespace bebone::gfx;
using namespace bebone::common;

int main() {
    RenderingEngine::preinit();
        
    Window window("Window example");

    while (!window.closing()) {

        glfwPollEvents();
    }

    RenderingEngine::terminate();
    return 0;
}