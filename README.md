# Gromit Game Engine

A simple and **unoptimized** game engine built for learning how to make game engines.

---

### Event System
- You can register to listen to any event by specifying the event class type, listener, and callback:  
  `REG_EVENT(WindowsResizeEvent, this, DoSomethingWindow);`
- Trigger an event by calling:  
  `TRIG_EVENT(MouseClickEvent, 0);` (pass in the required parameters)
- The event system queues all events and executes them when `PerFrame` is called.

---

### Logging
- Logging is a simple wrapper around the `spdlog` library.

---

### Application
- There is only **one** application instance in the engine, which must be implemented on the executable side.
- It handles startup/shutdown of all engine managers and runs the game loop until told to exit.

---

### Window / WindowManager
- There is an interface for `Window` and `WindowManager`, accessible from the executable.
- All implementation details are hidden and platform-dependent.
- Currently, only GLFW is supported (for OpenGL on Windows).

---

### PCH (Precompiled Header)
- A `pch.h` file acts as a precompiled header.
- CMake is configured to enable this for Visual Studio builds.

---

### Entry Point
- Keep the `EntryPoint` file minimal.
- It should only initialize and run the application.

---

### Dependencies

- **GLFW**  
  Handles window creation, input, and OpenGL context management.

- **GLAD**  
  Manages OpenGL function loading.

- **spdlog**  
  A fast, header-only logging library used for engine-wide debug/info/error logging.

---

### Gromit Example Application
// TODO: Add details and usage example.
