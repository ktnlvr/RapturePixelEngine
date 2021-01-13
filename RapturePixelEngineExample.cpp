#include <stdio.h>

#include "RapturePixelEngine.hpp"


int main() {
    RapturePtr engine = RapturePixelEngine::instance();

    engine->platform->CreateWindow(16, 16, 256, 256, "Hello, world!");
    engine->platform->CreateGraphics();
    engine->platform->ShowWindow();
    getchar();
    return 0;
}