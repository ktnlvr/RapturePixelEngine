#ifndef _RAPTURE_PIXEL_ENGINE_H_INCLUDED
#define _RAPTURE_PIXEL_ENGINE_H_INCLUDED

#include <cstring>
#include <stdlib.h>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <functional>

#ifdef __linux__
#include <X11/Xlib.h>
#endif

// ---------------------------
// --- CLASSES AND STRUCTS ---
// ---------------------------
#pragma region CLASSES AND STRUCTS
namespace rpe {
    /// POD (Plain old data) event object
    struct Event {
        /// Type of the occured event
        enum class EventType : uint8_t {
            NONE = 0,
            KEY = 1,
        } type;
        
        /// Specific for EventType::Key
        enum class KeyEventType { PRESS = 0, RELEASE = 1, };

        union {
            struct 
            {
                KeyEventType type;
            } KeyEvent;
        };

        /// Create new empty event object
        Event() : type(EventType::NONE) {}
        /// Create a new event of a specific type
        Event(EventType type) : type(type) {}

        #ifdef __linux__
        /// Forge a new event based on XEVENT
        Event(const XEvent* xevent);
        #endif
    };


    class Platform {
    protected:
        Platform() = default;

    public:
        /// Get the only Platform instance
        static inline Platform* instance() {
            static Platform platform;
            return &platform;
        }

        // Singleton singleton singleton singleton

        Platform(const Platform&) = delete;
        Platform(Platform&&) = delete;
        Platform& operator=(const Platform&) = delete;
        Platform& operator=(Platform&&) = delete;

        /// Create the window and prepare the world!
        void CreateWindow(
            int x = 16, 
            int y = 16, 
            unsigned int width = 256, 
            unsigned int height = 256,
            const char* title = "RapturePixelEngine Window");
        /// Make graphics and initialize GL context
        void CreateGraphics();
        /// Show the window 
        void ShowWindow();
        /// Check if there is an event
        bool CheckEvent(Event& out);

    private:
    #ifdef __linux__
        Display* d;
        Window w;
    #endif
    };

    class RapturePixelEngine {
    protected:
        RapturePixelEngine() {
            platform = Platform::instance();
        }

        ~RapturePixelEngine() = default;

    public:
        Platform* platform = nullptr;

        int x, y;
        unsigned int width, height;
        const char* title;

        struct {
            std::function<void(const Event&)> OnEventCallback = [](const Event&){}; 
        } callbacks;

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

        void Construct(
            int x = 16, 
            int y = 16, 
            unsigned int width = 256, 
            unsigned int height = 256,
            const char* title = "RapturePixelEngine Window") {
            
            this->x = x, this->y = y, this->width = width, this->height = height,
            this->title = title;

            theThread = std::thread([]() { TheThread(); });
        }

        void Start(bool join) {
            isRunning = true;
            if (join) {
                theThread.join();
            }
        }

        /// Mutex lock for thread safety
        std::mutex mtx;
        /// Lock to prevent changes
        std::condition_variable lock;
        /// Defines if the thread is active or not
        std::atomic_bool isRunning{false};
        /// Main Engine thread
        std::thread theThread;

        static void TheThread() {
            // Instance reference
            auto instance = RapturePixelEngine::instance();
            auto platform = instance->platform;

            // Creation has to be called here, so the thread recieves control
            platform->CreateWindow(
                instance->x, 
                instance->y, 
                instance->width, 
                instance->height, 
                instance->title);
            platform->CreateGraphics();

            platform->ShowWindow();

            // Multithreading lock
            std::unique_lock<std::mutex> lock(instance->mtx);

            // Wait for isRunning to be true
            instance->lock.wait(lock, []() {
                return RapturePixelEngine::instance()->isRunning.load();
            });

            // Unlock all the locks!
            lock.unlock();
            instance->lock.notify_all();

            for(;;) {
                Event event;
                if(instance->platform->CheckEvent(event)) {
                    instance->callbacks.OnEventCallback(event);
                }
            }
        }
    };
    #pragma endregion // CLASSES AND STRUCTS 

    // Pointer type for RapturePixelEngine
    using RapturePtr = RapturePixelEngine*;
}
// ------------------------------
// --- METHOD IMPLEMENTATIONS ---
// ------------------------------ 
#pragma region METHOD IMPLEMENTATIONS
#ifdef __linux__
void rpe::Platform::CreateWindow(
    int x, 
    int y, 
    unsigned int width, 
    unsigned int height,
    const char* title) {

    // Try open monitor
    d = XOpenDisplay(NULL);

    // Halt if couldn't
    if(d == nullptr) {
        printf("Can't connect X server.");
        std::exit(1);
    }

    int screen = XDefaultScreen(d);

    w = XCreateSimpleWindow(
        // display, parent window
        d, RootWindow(d, screen),
        // x, y, width, height 
        x, y, width, height,
        // border with, border, background
        1, XBlackPixel(d, screen), XWhitePixel(d, screen));

    XSelectInput(d, w, 
    ExposureMask | KeyPressMask | KeyReleaseMask);
    XStoreName(d, w, title);
}

void rpe::Platform::CreateGraphics() {
    // TODO
}

void rpe::Platform::ShowWindow() {
    XMapWindow(d, w);
    XFlush(d);
}

bool rpe::Platform::CheckEvent(Event& out) {
    XEvent tmp;
    bool ret = XCheckWindowEvent(d, w, 
        ExposureMask | KeyPressMask | KeyReleaseMask, 
        &tmp);

    switch (tmp.type)
    {
    case KeyPress:
        out = Event(Event::EventType::KEY);
        out.KeyEvent.type = Event::KeyEventType::PRESS;
        break;

    case KeyRelease:
        out = Event(Event::EventType::KEY);
        out.KeyEvent.type = Event::KeyEventType::RELEASE;
        break;

    default:
        out = Event(Event::EventType::NONE);
        break;
    }

    return ret;
}
#endif // __linux__

#pragma endregion // METHOD IMPLEMENTATIONS

#endif // _RAPTURE_PIXEL_ENGINE_H_INCLUDED
