#pragma once


#include <AllegroFlare/FrameAnimation/Animation.hpp>
#include <AllegroFlare/FrameAnimation/Book.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Base.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/Base.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro.h>
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
            class Basic2D : public AllegroFlare::Prototypes::Platforming2D::Entities::Base
            {
            public:
               static constexpr char* TYPE = (char*)"Entities/Basic2D";

            private:
               AllegroFlare::Placement2D place;
               AllegroFlare::Placement2D velocity;
               ALLEGRO_BITMAP* bitmap;
               AllegroFlare::Placement2D bitmap_placement;
               std::string bitmap_alignment_strategy;
               bool bitmap_flip_h;
               AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base* movement_strategy;
               AllegroFlare::FrameAnimation::Book* animation_book;
               AllegroFlare::FrameAnimation::Animation animation;
               bool draw_debug;
               ALLEGRO_COLOR debug_box_color;
               static void assign_alignment_strategy_values(AllegroFlare::Placement2D* parent_placement=nullptr, ALLEGRO_BITMAP* bitmap=nullptr, float* bitmap_x=nullptr, float* bitmap_y=nullptr, float* bitmap_align_x=nullptr, float* bitmap_align_y=nullptr, std::string bitmap_alignment_strategy="centered");

            protected:


            public:
               float& x;
               float& y;
               float& width;
               float& height;
               float& vx;
               float& vy;
               Basic2D(AllegroFlare::FrameAnimation::Book* animation_book=nullptr);
               virtual ~Basic2D();

               void set_place(AllegroFlare::Placement2D place);
               void set_velocity(AllegroFlare::Placement2D velocity);
               void set_bitmap(ALLEGRO_BITMAP* bitmap);
               void set_bitmap_placement(AllegroFlare::Placement2D bitmap_placement);
               void set_bitmap_flip_h(bool bitmap_flip_h);
               void set_movement_strategy(AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base* movement_strategy);
               void set_animation_book(AllegroFlare::FrameAnimation::Book* animation_book);
               void set_draw_debug(bool draw_debug);
               void set_debug_box_color(ALLEGRO_COLOR debug_box_color);
               AllegroFlare::Placement2D get_place() const;
               AllegroFlare::Placement2D get_velocity() const;
               ALLEGRO_BITMAP* get_bitmap() const;
               AllegroFlare::Placement2D get_bitmap_placement() const;
               std::string get_bitmap_alignment_strategy() const;
               bool get_bitmap_flip_h() const;
               AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base* get_movement_strategy() const;
               AllegroFlare::FrameAnimation::Book* get_animation_book() const;
               bool get_draw_debug() const;
               ALLEGRO_COLOR get_debug_box_color() const;
               AllegroFlare::Placement2D &get_place_ref();
               AllegroFlare::Placement2D &get_velocity_ref();
               AllegroFlare::Placement2D &get_bitmap_placement_ref();
               void set_bitmap_alignment_strategy(std::string bitmap_alignment_strategy="[unset-bitmap_alignment_strategy]");
               virtual void update() override;
               void refresh_bitmap_to_current_animation_frame();
               virtual void on_collision_update(AllegroFlare::Vec2D previous_place_position={}, AllegroFlare::Vec2D previous_velocity_position={}, AllegroFlare::Vec2D new_place_position={}, AllegroFlare::Vec2D new_velocity_position={}, std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo>* collision_step_result={});
               virtual void draw() override;
               void fit_to_bitmap();
               void disable_bitmap_alignment_strategy();
               void set_animation_playback_rate(float multiplier=1.0f);
               bool get_animation_finished();
               int get_current_animation_frame_num();
               void set_animation(std::string animation_name="[unset-animation_name]");
            };
         }
      }
   }
}



