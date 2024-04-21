# Update entities
- player is updated
- all entities are updated (if tracking player, tracking values are set)

# Move entities in environment
- step collision with environment
  - call to each entity->on_collision_update(...)

# Handle specific types of collisions in a preferencial order

```cpp
      // Evaluate entity collisions
      update_entity_collisions_with_damage_zones();

      // Evaluate player collisions on collectables
      // TODO: allow this function to run without being coupled with a "player_controlled_entity"
      if (player_controlled_entity) update_player_collisions_with_collectables();

      // Evaluate player collisions on the goalposts
      // TODO: allow this function to run without being coupled with a "player_controlled_entity"
      if (player_controlled_entity) update_player_collisions_with_goalposts();

      // Evaluate player collisions on save_points
      // TODO: allow this function to run without being coupled with a "player_controlled_entity"
      if (player_controlled_entity) update_player_collisions_with_save_points();

      // Evaluate player collisions on boss_zones
      // TODO: allow this function to run without being coupled with a "player_controlled_entity"
      if (player_controlled_entity) update_player_collisions_with_boss_zones();

      // Evaluate player collisions on entities tagged with COLLIDES_WITH_PLAYER
      // TODO: allow this function to run without being coupled with a "player_controlled_entity"
      if (player_controlled_entity) update_player_collisions_with_COLLIDES_WITH_PLAYER();

      // Evaluate damage zones on player
      //if (player_controlled_entity) update_player_collisions_with_damage_zones();

      // Delete entities flagged to be deleted
      cleanup_entities_flagged_for_deletion();

      // Update the camera
      if (!camera_control_strategy && player_controlled_entity)
      {
         camera.position.x = player_controlled_entity->x;
         camera.position.y = player_controlled_entity->y;
      }
      if (camera_control_strategy) camera_control_strategy->update();

      // Check for player death
      if (player_controlled_entity) check_and_respond_if_player_death();
```


```
  - name: update_player_collisions_with_COLLIDES_WITH_PLAYER
    private: true
    guards: [ player_controlled_entity ]
    body: |
      using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;
      std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> _entities = get_current_map_entities();
      AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&_entities);

      float player_x = player_controlled_entity->x;
      float player_y = player_controlled_entity->y;
      AllegroFlare::Placement2D &player_placement = player_controlled_entity->get_place_ref();

      for (auto &entity : collection_helper.select_collides_with_player())
      {
         // TODO: Be alert that multiple collisions could cause multiple callbacks and some potentially undefined
         // result state
         //if (entity->get_place_ref().collide(&pla->get_placement_ref())); //player_x, player_y, 0, 0, 0, 0))
         if (entity->get_place_ref().collide(player_placement)) //player_x, player_y, 0, 0, 0, 0))
         {
            // OPTION 1: Do some collision response within the entity
            entity->on_collides_with_player(player_controlled_entity);
            // OPTION 2: Do some collision response within the entity
            on_player_controlled_entity_collision_with_entity(player_controlled_entity, entity);
         }
      }
      return;
    body_dependency_symbols:
      - AllegroFlare::Prototypes::Platforming2D::EntityFlagNames
      - AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper
```


```
  - name: on_player_controlled_entity_collision_with_entity
    private: true
    virtual: true
    parameters:
      - name: player_controlled_entity
        type: AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*
        default_argument: nullptr
      - name: entity
        type: AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*
        default_argument: nullptr
    guards: [ player_controlled_entity, entity ]
    body: |
      // This is for blut collisions on every pass
      return;


  - name: on_player_controlled_entity_collision_with_entity
    private: true
    virtual: true
    parameters:
      - name: player_controlled_entity
        type: AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*
        default_argument: nullptr
      - name: entity
        type: AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*
        default_argument: nullptr
    guards: [ player_controlled_entity, entity ]
    body: |
      return;


  - name: on_enter_player_controlled_entity_collision_with_entity
    private: true
    virtual: true
    parameters:
      - name: player_controlled_entity
        type: AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*
        default_argument: nullptr
      - name: entity
        type: AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*
        default_argument: nullptr
    guards: [ player_controlled_entity, entity ]
    body: |
      return;


  - name: on_exit_player_controlled_entity_collision_with_entity
    private: true
    virtual: true
    parameters:
      - name: player_controlled_entity
        type: AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*
        default_argument: nullptr
      - name: entity
        type: AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*
        default_argument: nullptr
    guards: [ player_controlled_entity, entity ]
    body: |
      return;


  - name: on_hold_player_controlled_entity_collision_with_entity
    private: true
    virtual: true
    parameters:
      - name: player_controlled_entity
        type: AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*
        default_argument: nullptr
      - name: entity
        type: AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*
        default_argument: nullptr
    guards: [ player_controlled_entity, entity ]
    body: |
      return;


  - name: on_hold_player_controlled_entity_non_collision_with_entity
    private: true
    virtual: true
    parameters:
      - name: player_controlled_entity
        type: AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*
        default_argument: nullptr
      - name: entity
        type: AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*
        default_argument: nullptr
    guards: [ player_controlled_entity, entity ]
    body: |
      return;
```

in your Gameplay/Screen:

 have a case that handles "on_player_controlled_entity_collision_with_entity"


In the entity, you also have these methods (below), but they should be avoided
generally for complex interactions (emitting events, modifying other classes).
The general design approach is to avoid complex iteractions in the classes themselves and handle
those types of interactions in the Gameplay/Screen, using the methods above.

```
  - name: on_enter_collision_with_player
    virtual: true
    parameters:
      - name: player_controlled_entity
        type: AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*
        default_argument: nullptr
    body: |
      // NOTE: This method will only be called if this entity is tagged with COLLIDES_WITH_PLAYER and there is a
      // collision that occurs during the physics step
      return;


  - name: on_hold_collision_with_player
    virtual: true
    parameters:
      - name: player_controlled_entity
        type: AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*
        default_argument: nullptr
      - name: duration
        type: float
        default_argument: 0.0f
    body: |
      // NOTE: This method will only be called if this entity is tagged with COLLIDES_WITH_PLAYER and there is a
      // collision that occurs during the physics step
      return;


  - name: on_exit_collision_with_player
    virtual: true
    parameters:
      - name: player_controlled_entity
        type: AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*
        default_argument: nullptr
    body: |
      // NOTE: This method will only be called if this entity is tagged with COLLIDES_WITH_PLAYER and there is a
      // collision that occurs during the physics step
      return;


  - name: on_hold_non_collision_with_player
    virtual: true
    parameters:
      - name: player_controlled_entity
        type: AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*
        default_argument: nullptr
      - name: duration
        type: float
        default_argument: 0.0f
    body: |
      // NOTE: This method will only be called if this entity is tagged with COLLIDES_WITH_PLAYER and there is a
      // collision that occurs during the physics step
      return;
```



