#ifndef _RAPTURE_PIXEL_ENGINE_H_INCLUDED
#define _RAPTURE_PIXEL_ENGINE_H_INCLUDED

class Platform {
protected:
    Platform() = default;

public:
    // Get the only Platform instance
    static inline Platform* instance() {
        static Platform platform;
        return &platform;
    }

    // Singleton singleton singleton singleton

    Platform(const Platform&) = delete;
    Platform(Platform&&) = delete;
    Platform& operator=(const Platform&) = delete;
    Platform& operator=(Platform&&) = delete;

};

class RapturePixelEngine {
protected:
    RapturePixelEngine() {
        platform = Platform::instance();
    }

    ~RapturePixelEngine() = default;

public:
    Platform* platform = nullptr;

    // Get the only RapturePixelEngine instance
    static inline RapturePixelEngine* instance() {
        static RapturePixelEngine engine;
        return &engine;
    }

    // No copying or assigning, it's a singleton all in all

    RapturePixelEngine(const RapturePixelEngine&) = delete;
    RapturePixelEngine(RapturePixelEngine&&) = delete;
    RapturePixelEngine& operator=(const RapturePixelEngine&) = delete;
    RapturePixelEngine& operator=(RapturePixelEngine&&) = delete;
};

// Pointer type for RapturePixelEngine
using RapturePtr = RapturePixelEngine*;

#endif // _RAPTURE_PIXEL_ENGINE_H_INCLUDED