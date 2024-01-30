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
            std::string const INVISIBLE = "invisible";

            std::string const TMJ_OBJECT_CLASS = "tmj_object_class";
            std::string const TYPE = "type";
            std::string const GOALPOST = "goalpost";
            std::string const DOOR = "door";

            std::string const ON_MAP_NAME = "on_map_name";
            std::string const MAP_NAME = "map_name";
            std::string const EPHEMERAL = "ephemeral";



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



