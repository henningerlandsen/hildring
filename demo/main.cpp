#include "Window.h"

int main(int argc, char** argv) {

    Window window(640, 480, "Hello, World!");
    
    while(window.update()) {
        
    }

    return 0;
}
