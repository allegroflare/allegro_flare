# Adding Bosses


## BossZones

A BossZone is a rectangular area in the map where you engage in a boss fight.
In Tiled, Bosses are represented by a rectangle with the `class` name "boss_zone".
Upon entering the rectangle area, the boss battle will trigger.

Entering has the following side effects:
- `Platforming2D::Screen::in_boss_zone` is set to true
- `Platforming2D::Screen::current_boss_zone` is set to true current boss zone
- `Platforming2D::Screen::on_enter_boss_zone` is called. You should override
  this in your base class, and define your game's specific behavior.

Important factors in a BossZone:
- A BossZone should be flagged with `BOSS_ZONE`. It does not need
  `COLLIDES_WITH_PLAYER`.

### Code Example: Creating a BossZone

This code example from JourneyOfTheCat/TMJObjectLoadCallback:

```
      else if (object_type == "boss_zone")
      {
         AllegroFlare::Prototypes::Platforming2D::Entities::BossZone *boss_zone_entity =
            new AllegroFlare::Prototypes::Platforming2D::Entities::BossZone;

         boss_zone_entity->x = x;
         boss_zone_entity->y = y;
         boss_zone_entity->width = width;
         boss_zone_entity->height = height;
         boss_zone_entity->get_place_ref().align = { 0, 0 };

         boss_zone_entity->set(TMJ_OBJECT_TYPE, object_type);
         boss_zone_entity->set(TMJ_OBJECT_ID, id);
         boss_zone_entity->set(TMJ_OBJECT_NAME, name);

         boss_zone_entity->set(
             AllegroFlare::Prototypes::Platforming2D::EntityFlagNames::NOT_AFFECTED_BY_GRAVITY
           );
         boss_zone_entity->set(
             AllegroFlare::Prototypes::Platforming2D::EntityFlagNames::DOES_NOT_COLLIDE_WITH_WORLD
           );

         // NOTE: Player collisions are handled manually by the Platforming2D/Screen, specificaly because of this
         // flag:
         boss_zone_entity->set(
               AllegroFlare::Prototypes::Platforming2D::EntityFlagNames::TYPE,
               BOSS_ZONE
            ); // Will be handled in Platforming2D::Screen::update_player_collisions_with_boss_zones

         entity_pool->push_back(boss_zone_entity);
      }
```

## Entities/Boss

### Initiating the Boss battle:

Typically when entering a boss zone for the first time, you would `create` the
boss object at that time (if it does not exist and has not been defeated, more on
that in a sec.).

In your boss class:
  - Your boss class should derive from `Platforming2D::Entities::Boss`.
  - Call `Platforming2D::Entities::Boss::call_on_death_being_callback()` when the
    boss's death sequence begins;
  - Call `Platforming2D::Entities::Boss::call_on_death_end_callback()` when the
    boss's death sequence is finished;
  - Provide overrides for "get_health_bar_value" and "get_health_bar_max_value"
  - Use the "get_health_bar_value" and "get_health_bar_max_value" in your hud

In `on_enter_boss_zone`, do the following:
  - Evalute the boss_zone to decide if the boss already exists or has been
    defeated.
  - Create the boss entity `boss_entity`
  - Add add it to the `entity_pool`
  - Set it to the `boss_zone`, e.g. `boss_zone.set_boss(boss_entity)`.
    Typically, your the `current_boss_zone` is referenced in the hud to
    determine drawing the boss's health meter, etc.
  - Add an `on_death_end_callback` - this is the callback that is called when
    the boss *finishes* its death sequence.  (There is also a
    `on_death_begin_sequene`, which you could use to for other purposes as well.)

Other things you might do:
  - In the `on_enter_boss_zone` callback, trigger boss music.
  - Spawn/trigger barriers to the boss lair entrance/exit.
  - There is also `on_exit_boss_zone` if you're interesting in handling non-fixed boss encounters. 


In the boss's `on_death_end_callback`:
  - Flag the boss zone `boss_is_defeated` as true `boss_zone->set_boss_is_defeated(true);`.
    (You might do this in `on_death_begin_callback`.)
  - Turn off boss music, or start normal level music.
  - Remove barriers to the boss lair entrance/exit.
  - Consider saving progress on a defeated boss.


## Code Examples

### Platforming2D/Screen on_enter_boss_zone

```
  - name: on_enter_boss_zone
    virtual: true
    override: true
    parameters:
      - name: boss_zone
        type: AllegroFlare::Prototypes::Platforming2D::Entities::BossZone*
        default_argument: nullptr
    guards: [ boss_zone ]
    body: |
      using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

      std::string tmj_object_name = boss_zone->get(TMJ_OBJECT_NAME);

      if (false == true) {}
      else if (tmj_object_name == "boss_zone_2d")
      {
         if (boss_zone->get_boss() == nullptr) // TODO: Make a "has_boss"
         {
            // Create the boss entity
            float x = boss_zone->x + 64; // TODO: Improve these placeholder numbers
            float y = boss_zone->y +128; // TODO: Improve these placeholder numbers
            float width = 64;
            float height = 64;

            auto boss_entity = SomePlatformer::Entities::Bosses::Level3Boss::construct(
                  x,
                  y,
                  width,
                  height,
                  &animation_book,
                  &get_flat_color_shader_ref(),
                  get_event_emitter()
               );

            // Create the callback for the entity when the boss is defeated
            boss_entity->set_on_death_end_callback(
               [this, boss_zone](AllegroFlare::Prototypes::Platforming2D::Entities::Boss *boss, void *data){
                  // Flag the boss zone as defeated
                  boss_zone->set_boss_is_defeated(true);

                  // Make the barriers non-solid
                  auto entities = find_dynamic_tiles_in_group_name("boss_zone_2d_barriers");
                  for (auto &entity : entities) entity->make_nonsolid();
               }
            );

            // Add some critical properties to the boss
            boss_entity->set(COLLIDES_WITH_PLAYER);
            boss_entity->set(ON_MAP_NAME, get_currently_active_map_name());

            // Add the boss to the entity pool
            get_entity_pool_ref().push_back(boss_entity);

            // TODO: Start boss music?

            // Fill the barriers blocking the entrance and exit
            auto entities = find_dynamic_tiles_in_group_name("boss_zone_2d_barriers");
            for (auto &entity : entities) entity->make_solid();

            // Give the "boss_zone" a pointer to the associated created boss entity
            boss_zone->set_boss(boss_entity);
         }
      }

      return;
    body_dependency_symbols:
      - SomePlatformer::Entities::Bosses::Level3Boss
```
