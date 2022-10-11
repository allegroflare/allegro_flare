#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <Wicked/Entities/Basic2D.hpp>
#include <Wicked/Entities/Enemies/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Wicked
{
   namespace Entities
   {
      class Basic2DFactory
      {
      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         ALLEGRO_COLOR enemy_debug_box_color;
         ALLEGRO_COLOR player_collectable_box_color;
         ALLEGRO_COLOR goalpost_box_color;

      protected:


      public:
         Basic2DFactory(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         ~Basic2DFactory();

         Wicked::Entities::Basic2D* create_from_bitmap_filename(std::string map_name="[map-name-not-set]", std::string bitmap_filename="bitmap-filename-that-has-not-been-set.png", std::string bitmap_alignment_strategy="centered");
         Wicked::Entities::Basic2D* create_for_aabb2d(std::string map_name="[map-name-not-set]", float width=(16.0f-1.0f), float height=(16.0f-1.0f));
         Wicked::Entities::Basic2D* create_player_projectile(std::string map_name="[map-name-not-set]", float x=0.0f, float y=0.0f, float width=(8.0f-1.0f), float height=(8.0f-1.0f), AllegroFlare::vec2d vector=AllegroFlare::vec2d(0.0f, 1.0f), float magnitude=1.0f);
         Wicked::Entities::Enemies::Base* create_enemy_move_left(std::string map_name="[map-name-not-set]", float x=0.0f, float y=0.0f, float width=(16.0f-1.0f), float height=(16.0f-1.0f));
         Wicked::Entities::Enemies::Base* create_tracking_enemy(std::string map_name="[map-name-not-set]", Wicked::Entities::Basic2D* tracked_entity=nullptr, float x=0.0f, float y=0.0f, float width=(16.0f-1.0f), float height=(16.0f-1.0f));
         Wicked::Entities::Enemies::Base* create_flapping_enemy(std::string map_name="[map-name-not-set]", float x=0.0f, float y=0.0f, float width=(16.0f-1.0f), float height=(16.0f-1.0f), float target_elevation=0.0f, float flap_strength=1.0f, float flap_recovery_rate=0.1f);
         Wicked::Entities::Basic2D* create_collectable(std::string map_name="[map-name-not-set]", float x=0.0f, float y=0.0f);
         Wicked::Entities::Basic2D* create_door(std::string map_name="[map-name-not-set]", float x=0.0f, float y=0.0f, std::string target_map_name="[unset-target-map-name]", float target_spawn_x=0.0f, float target_spawn_y=0.0f);
         Wicked::Entities::Basic2D* create_game_event_door(std::string map_name="[map-name-not-set]", float x=0.0f, float y=0.0f, std::string game_event_name_to_emit="[unset-game_event_name_to_emit]");
         Wicked::Entities::Basic2D* create_goalpost(std::string map_name="[map-name-not-set]", float x=0.0f, float y=0.0f);
         Wicked::Entities::Basic2D* create_tile_map(std::string map_json_filename="[a-map-tmj-filename-that-is-not-set]", std::string map_name="[map-name-not-set]");
      };
   }
}



