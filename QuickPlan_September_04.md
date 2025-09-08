Rename model to entity

Implement load methods for entity and material

Make Component class, with only transform and meshrender for now

Make a conversion from entityasset to entity with components specified in JSON

Make EntityManager which handles all entities added to the world, can just be a vector wrapper for now

In EntityManager, loop through all entities alive and if they have the mesh renderer component then create a RenderObject (later can cache in the component) and send to the renderer

Have renderer only draw this list in its update method