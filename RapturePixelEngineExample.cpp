#include <stdio.h>

#include "RapturePixelEngine.hpp"


int main(int argc, char *argv[]) {
    // if you are not feeling like writing this everywhere
    using namespace rpe;    

    // Retrieve the engine instance
    RapturePtr engine = RapturePixelEngine::instance();

    // Register a callback for general event
    engine->callbacks.OnKey = [](const Event& e) {
        if(e.keyEvent.type == Event::KeyEventType::PRESS) {
            printf("Pressed\n");
        } else if (e.keyEvent.type == Event::KeyEventType::RELEASE) {
            printf("Released\n");
        }
    };

    // Create the instance and prepare
    engine->Construct();
    // Run the thing and join it to the main thread
    engine->Start(true);

    // whooosh and halt
    return 0;
}
