# Rapture Pixel Engine
![GitHub file size in bytes](https://img.shields.io/github/size/youngman114/RapturePixelEngine/RapturePixelEngine.hpp?label=RapturePixelEngine.hpp%20size)

Straightforward and humble event-driven engine for (and not only limited by) 
pixel graphics.

> Best rendering engine **ever!** (c) Me

## Installation

1. Download the header file (`RapturePixelEngine.hpp`)

2. Include the header in your application (or use `RapturePixelEngineExample.cpp`,
skip to Compile & Link)

## Usage

The project is kept clean, so no inheritance or complex structures. Everything
you need to worry about is put into the `RapturePixelEngine` type, in 
`namespace rpe`. System dependent details are obscured by the `Platform` type.
As only one window intstance can be handled, all the operations are performed
over a pointer to an already existing instance, which is retrieved via an
autological static method `RapturePixelEngine::instance()`;

3. Write some code

```cpp
// Whoosh, now in your project
#include "RapturePixelEngine.hpp"

// your classical main function
int main() {
    // use namespace to avoid repetition
    using namespace rpe;

    // singleton unique instance pointer
    RapturePtr engine = RapturePixelEngine::instance();
    // configure the object
    engine.Construct();
    // start the window!
    engine.Start();

    return 0;
}
```

4. Callbacks are events, triggered upon certain conditions. A good example
would be `OnEventCallback`, the one triggered on any window event. Later more 
scoped callbacks might occur. For more infromation look at the 
types, code won't lie.

```cpp
RapturePixelEngine::instance()->callbacks.OnEventCallback = [](const Event&) {
    // I fire when an event is caught!
    // The event is passed as a constant reference
}
```

5. Link the static libraries and compile your project. It uses two of statics,
present on most computers. If you can't link with them seek installation
guidance for your system.

Linux:
```sh
g++ your_desired_file.cpp -lX11 -lpthread -o your_desired_output.o 
```

Windows:
__temporarily unavailable, expect soon!__ 

6. Run the program!

Linux:
```sh
./your_desired_output.o
```

## Contributing

Pull requests are very welcome. 
For major changes, please open an issue first  in order to discuss the need. 
Use and create!


## License

[LICENSE](./LICENSE)

