#include "Window.h"

#include <thread>
#include <chrono>

using namespace std::chrono_literals;

int main(int argc, char** argv) 
{

    Window window(640, 480, "Hello, World!");
    
    while(window.update()) 
    {
        std::this_thread::sleep_for(16ms);
    }

    return 0;
}
