#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FrameAnimation/Book.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2DFactory.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Enemies/Base.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/FrameAnimated2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/TileMaps/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/TMJObjectLoaderObjectCustomProperties.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro.h>
#include <functional>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace Entities
         {
            class Basic2DFactory
            {
            private:
               AllegroFlare::BitmapBin* bitmap_bin;
               AllegroFlare::FrameAnimation::Book* animation_book;
               bool init_entities_drawing_debug;
               ALLEGRO_COLOR enemy_debug_box_color;
               ALLEGRO_COLOR player_collectable_box_color;
               ALLEGRO_COLOR goalpost_box_color;

            protected:


            public:
               Basic2DFactory(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FrameAnimation::Book* animation_book=nullptr);
               ~Basic2DFactory();

               void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
               void set_animation_book(AllegroFlare::FrameAnimation::Book* animation_book);
               void set_init_entities_drawing_debug(bool init_entities_drawing_debug);
               AllegroFlare::BitmapBin* get_bitmap_bin() const;
               AllegroFlare::FrameAnimation::Book* get_animation_book() const;
               AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* create_from_bitmap_filename(std::string map_name="[map-name-not-set]", std::string bitmap_filename="bitmap-filename-that-has-not-been-set.png", std::string bitmap_alignment_strategy="centered") const;
               AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* create_for_aabb2d(std::string map_name="[map-name-not-set]", float width=(16.0f-1.0f), float height=(16.0f-1.0f)) const;
               AllegroFlare::Prototypes::Platforming2D::Entities::FrameAnimated2D* create_frame_animated(std::string map_name="[map-name-not-set]", float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f, std::string initial_animation_name="[unset-initial_animation_name]", std::string bitmap_alignment_strategy="centered") const;
               AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* create_player_projectile(std::string map_name="[map-name-not-set]", float x=0.0f, float y=0.0f, float width=(8.0f-1.0f), float height=(8.0f-1.0f), AllegroFlare::vec2d vector=AllegroFlare::vec2d(0.0f, 1.0f), float magnitude=1.0f) const;
               AllegroFlare::Prototypes::Platforming2D::Entities::Enemies::Base* create_enemy(std::string map_name="[map-name-not-set]", float x=0.0f, float y=0.0f, float width=(16.0f-1.0f), float height=(16.0f-1.0f)) const;
               AllegroFlare::Prototypes::Platforming2D::Entities::Enemies::Base* create_enemy_move_left(std::string map_name="[map-name-not-set]", float x=0.0f, float y=0.0f, float width=(16.0f-1.0f), float height=(16.0f-1.0f)) const;
               AllegroFlare::Prototypes::Platforming2D::Entities::Enemies::Base* create_tracking_enemy(std::string map_name="[map-name-not-set]", AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* tracked_entity=nullptr, float x=0.0f, float y=0.0f, float width=(16.0f-1.0f), float height=(16.0f-1.0f)) const;
               AllegroFlare::Prototypes::Platforming2D::Entities::Enemies::Base* create_flapping_enemy(std::string map_name="[map-name-not-set]", float x=0.0f, float y=0.0f, float width=(16.0f-1.0f), float height=(16.0f-1.0f), float target_elevation=0.0f, float flap_strength=1.0f, float flap_recovery_rate=0.1f) const;
               AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* create_collectable(std::string map_name="[map-name-not-set]", float x=0.0f, float y=0.0f) const;
               AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* create_door(std::string map_name="[map-name-not-set]", float x=0.0f, float y=0.0f, std::string target_map_name="[unset-target-map-name]", float target_spawn_x=0.0f, float target_spawn_y=0.0f) const;
               AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* create_game_event_door(std::string map_name="[map-name-not-set]", float x=0.0f, float y=0.0f, std::string game_event_name_to_emit="[unset-game_event_name_to_emit]") const;
               AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* create_goalpost(std::string map_name="[map-name-not-set]", float x=0.0f, float y=0.0f) const;
               AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D* create_tile_map(std::string map_name="[map-name-not-set]", std::string map_json_filename="[a-map-tmj-filename-that-is-not-set]", std::string tile_atlas_bitmap_identifier="[unset-tile_atlas_bitmap_identifier]") const;
               static void create_entities_from_map__tmj_obj_loader_callback_func(std::string object_type="[unset-object_type]", float x=0.0f, float y=0.0f, float width=0.0f, float height=0.0f, AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties custom_properties={}, void* data=nullptr);
               static void create_entities_from_map__tmj_obj_loader_with_callback_provided_func(std::string object_type="[unset-object_type]", float x=0.0f, float y=0.0f, float width=0.0f, float height=0.0f, AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties custom_properties={}, void* data=nullptr);
               std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> create_entities_from_map(std::string map_tmj_filename="[unset-map_tmj_filename]", std::string map_name="[unset-map_name]", std::function<void( std::string, float, float, float, float, AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties, std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>*, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory*, void*) > callback={}, void* callback_data=nullptr);
            };
         }
      }
   }
}



