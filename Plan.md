# 🛠️ Gromit Engine: Asset System Development Plan

A concise but detailed plan for implementing a packaged and efficient asset system in the Gromit game engine.

---

## 📦 Asset Packaging

### Goals
- Reduce file count and improve load times.
- Compress asset data.
- Provide fast random access to individual assets.

### Tasks
- Create a tool to **pack assets** into compressed `.pak` files.
- Design a simple **asset index**:
  - Maps asset names or IDs to file offsets and sizes.
- Write runtime code to:
  - Read from `.pak` files.
  - Extract and decompress specific assets efficiently.
- Implement an **AssetManager**:
  - Load assets on demand.
  - Track references and unload unused assets.

---

## 📄 Serialization & Loading

### Goals
- Define a lightweight scene or game data format.
- Avoid hardcoding asset references.

### Tasks
- Create a custom **binary or JSON** format:
  - References assets by name or ID.
  - Describes scene, entity, and component data.
- Engine reads this file and:
  - Instantiates scene elements.
  - Loads required assets via the AssetManager.

---

## 🎮 Asset Types to Load

### Sprites
- Load 2D images (e.g., PNG).
- Convert to GPU textures.
- Support metadata (pivot, atlas rect).

### Audio
- Support formats like WAV or OGG.
- Stream long music, fully load short effects.
- Integrate with an audio backend.

### 3D Models
- Use **Assimp** for FBX, OBJ, etc.
- Convert to internal mesh/material formats.
- Support basic animations if needed.

### Materials & Shaders
- See next section.

---

## ✨ Shader Loading System

### Goals
- Dynamically load, compile, and cache shaders.
- Allow hot-reloading during development.
- Integrate with materials and asset system.

### Development Workflow
- Store shaders as text files: `.vert`, `.frag`, etc.
- Optionally define shader programs in `.shader.json`:
  ```json
  {
    "vertex": "default.vert",
    "fragment": "default.frag",
    "uniforms": ["u_MVP", "u_Texture"]
  }
