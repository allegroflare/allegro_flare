#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace EntityFlagNames
         {
            std::string const ADJACENT_TO_FLOOR = "on_ground";
            std::string const ADJACENT_TO_CEILING = "adjacent_to_ceiling";
            std::string const ADJACENT_TO_LEFT_WALL = "adjacent_to_left_wall";
            std::string const ADJACENT_TO_RIGHT_WALL = "adjacent_to_right_wall";

            std::string const NOT_AFFECTED_BY_GRAVITY = "not_affected_by_gravity";
            std::string const PLEASE_DELETE = "please_delete";
            std::string const DOES_NOT_COLLIDE_WITH_WORLD = "does_not_collide_with_world";
            std::string const COLLECTABLE_BY_PLAYER = "collectable_by_player";
            std::string const COLLIDES_WITH_PLAYER = "collides_with_player";
            std::string const CURRENTLY_COLLIDING_WITH_PLAYER = "currently_colliding_with_player";
            std::string const INVISIBLE = "invisible";
            std::string const DEAD = "dead";

            std::string const TMJ_OBJECT_TYPE = "tmj_object_type";
            std::string const TMJ_OBJECT_ID = "tmj_object_id";
            std::string const TMJ_OBJECT_NAME = "tmj_object_name";
            std::string const TARGET_DOOR_ID = "target_door_id"; // Value used in Tiled maps to specify ids
            std::string const TYPE = "type";
            std::string const GOALPOST = "goalpost";
            std::string const DOOR = "door";
            std::string const BOSS_ZONE = "boss_zone";
            std::string const SAVE_POINT = "save_point";
            std::string const TRACKS_PLAYER_CHARACTER_XY = "tracks_player_character_xy";

            std::string const TARGET_DOOR_NAME = "target_door_name";
            std::string const TARGET_DOOR_TMJ_ID = "target_door_tmj_id"; // Key used internally to represent which
                                                                         // door tmj_object_id is the target

            std::string const ON_MAP_NAME = "on_map_name"; // Used to set which map the current entity is in
            std::string const MAP_NAME = "map_name"; // Use to set a map name on the map(?)

            std::string const EPHEMERAL = "ephemeral"; // Means pure effect



            /*

            // some ideas:

            on_ground
            on_left_wall
            on_right_wall
            on_ceiling

            by_ceiling
            by_left_wall
            by_right_wall
            by_ground

            collides_with_world
            can_be_destroyed
            collides_with_player
            collides_with_enemies
            enemy_character
            player_character
            is_destroyed_when_off_screen
            is_destroyed_when_off_map
            affected_by_gravity

            */
         }
      }
   }
}



