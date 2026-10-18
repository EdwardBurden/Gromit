# Gromit

A hobby **C++20 game engine** built around OpenGL, with a service-based architecture, a GUID-driven JSON asset system and an event system.

> ⚠️ **Work in progress.** Gromit is under active development and is not ready for real use. Large parts are unfinished, APIs change without notice, and there is a lot of temporary code and TODOs. Expect rough edges, missing features and breaking changes.

## What's in the repo

| Project | Type | Description |
| --- | --- | --- |
| `Gromit` | Shared library | The engine itself |
| `GromitExample` | Executable | A sample application built on the engine |
| `GromitPackager` | Executable | An unfinished tool for packing asset folders into a `.grm` archive |

## Current state

Roughly working today:

- **Engine services** (`ServiceLocator`): logging, renderer, window manager, asset manager, event system and scene manager are registered at startup, started in order and shut down in reverse.
- **OpenGL renderer** behind a small render API abstraction (windows, contexts, shaders, textures, vertex and index buffers, vertex arrays, materials). The renderer enum lists DirectX and Vulkan, but only OpenGL is implemented.
- **Windowing and events** via GLFW. Window resize and mouse click events can be listened to with `REG_EVENT`.
- **Asset system**: assets are described by JSON files with GUIDs and identified from a folder at runtime. Types include entities, scenes, meshes, materials, shaders and textures. Meshes are imported with Assimp.
- **Scenes and entities**: scenes list entity instances that override component values (such as a transform's position or a mesh renderer's material), with transform and mesh renderer components so far.
- **Memory utilities**: a linear allocator and a pool allocator.

Planned or incomplete:

- The packager creates its header and entry list but does not yet write a `.grm` file.
- The event system is only partly built. The design in `Gromit/src/Gromit/EventSystem/Plan.txt` also covers one-line `SEND_EVENT` calls, listener priorities, consumable events, and generating new event types from a CSV.
- Only a single window is created at startup, and scene and camera handling are still basic.
- The render and application code still contains temporary placeholders.

## Building

### Requirements

- CMake 3.10 or newer
- A C++20 compiler. The project is set up for **MSVC** on **Windows**: the entry point is Windows-only (`#ifdef _WIN32`) and the build copies an MSVC-built Assimp DLL.
- OpenGL

Third-party libraries are used from `Gromit/dependencies`: GLFW, GLM, Assimp, spdlog, glad, nlohmann/json and stb_image. The matching sources are listed as git submodules under `Gromit/external` (spdlog, GLFW, GLM and Assimp), so clone with submodules if you want to rebuild them:

```bash
git clone --recurse-submodules https://github.com/EdwardBurden/Gromit.git
```

`Gromit/tools/rebuild_spd_debug.bat` and `rebuild_spd_release.bat` show how spdlog is rebuilt and installed into `dependencies`.

### Build steps

```bash
cmake -S . -B build
cmake --build build --config Debug
```

All binaries are written to `build/bin`. After building, the `assets` folder is copied next to the engine library and the `pack 1` folder next to the example, so run `GromitExample` from that output directory.

## Running the example

`GromitExample` opens a window, scans the `assets` and `pack 1` folders for asset definitions, and registers listeners for window resize and mouse click events. With the demo scene (GUID 5, `Test_Scene_1`):

- **Left click** unloads the scene.
- **Right click** loads the scene.

Check the console log to see events and engine messages.

## Using the engine

An application subclasses `Gromit::Application`, overrides `StartUp` and `Run`, and provides `CreateApplication()`:

```cpp
#include <Gromit.h>

class MyApp : public Gromit::Application
{
public:
    void StartUp() override
    {
        Application::StartUp();
        Gromit::ServiceLocator::GetService<Gromit::AssetManager>()->IdentifyAssets("assets");
    }
    void Run() override { Application::Run(); }
};

Gromit::Application* Gromit::CreateApplication() { return new MyApp(); }
```

The engine supplies `main`, which creates the application, runs the loop while `IsRunning()` is true and then shuts everything down.

## Project layout

```
.
├── CMakeLists.txt          Top level build
├── Gromit/
│   ├── assets/             Sample JSON assets, shaders and textures
│   ├── dependencies/       Third-party headers and libraries
│   ├── external/           Git submodules for the dependencies
│   ├── tools/              Dependency rebuild scripts
│   └── src/Gromit/
│       ├── AssetManagement/    Asset database, loading and asset types
│       ├── Core/               Linear and pool allocators
│       ├── EntityManagement/   Scenes and component instances
│       ├── EventSystem/        Events and listeners
│       ├── Logging/            spdlog wrapper
│       ├── Math/
│       ├── Render/             Renderer, camera, render commands
│       └── RenderAPIs/         API abstraction and the OpenGL backend
├── GromitExample/          Sample application and asset pack
└── GromitPackager/         Asset pack tool (unfinished)
```

## License

Released under the MIT License. See [LICENSE.txt](LICENSE.txt).
