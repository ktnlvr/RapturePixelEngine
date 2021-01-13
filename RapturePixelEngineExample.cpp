#include <stdio.h>

#include "RapturePixelEngine.hpp"


int main() {
    RapturePtr engine = RapturePixelEngine::instance();

    engine->Construct();
    engine->Start(true);
    return 0;
}