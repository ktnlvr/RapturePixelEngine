#include <stdio.h>

#include "RapturePixelEngine.hpp"


int main() {
    RapturePtr engine = RapturePixelEngine::instance();

    engine->platform->CreateWindow();
    engine->platform->CreateGraphics();
    engine->platform->ShowWindow();
    getchar();
    return 0;
}