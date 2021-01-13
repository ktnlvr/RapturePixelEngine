#include <stdio.h>

#include "RapturePixelEngine.hpp"


int main() {
    RapturePtr engine = RapturePixelEngine::instance();

    engine->callbacks.OnEventCallback = [](const Event& e) {
        switch (e.type)
        {
        case Event::EventType::KEY: {
            std::cout << (int)e.KeyEvent.type << "\n";
        } break;
        
        case Event::EventType::NONE:
        default:
            break;
        }
    };

    engine->Construct();
    engine->Start(true);
    return 0;
}