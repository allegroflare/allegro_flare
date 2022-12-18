#pragma once


#include <AllegroFlare/FrameAnimation/Animation.hpp>
#include <AllegroFlare/FrameAnimation/Book.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace Entities
         {
            class FrameAnimated2D : public AllegroFlare::Prototypes::Platforming2D::Entities::Base
            {
            public:
               static constexpr char* TYPE = (char*)"Entities/FrameAnimated2D";

            private:
               AllegroFlare::FrameAnimation::Book* animation_book;
               AllegroFlare::Placement2D place;
               AllegroFlare::Placement2D velocity;
               AllegroFlare::FrameAnimation::Animation animation;
               ALLEGRO_BITMAP* bitmap_internal;
               std::string bitmap_alignment_strategy;
               bool bitmap_flip_h;
               ALLEGRO_COLOR debug_box_color;
               static void assign_alignment_strategy_values(AllegroFlare::Placement2D* parent_placement=nullptr, ALLEGRO_BITMAP* bitmap=nullptr, float* bitmap_x=nullptr, float* bitmap_y=nullptr, std::string bitmap_alignment_strategy="centered");

            protected:


            public:
               FrameAnimated2D(AllegroFlare::FrameAnimation::Book* animation_book=nullptr);
               virtual ~FrameAnimated2D();

               void set_animation_book(AllegroFlare::FrameAnimation::Book* animation_book);
               void set_place(AllegroFlare::Placement2D place);
               void set_velocity(AllegroFlare::Placement2D velocity);
               void set_bitmap_alignment_strategy(std::string bitmap_alignment_strategy);
               void set_bitmap_flip_h(bool bitmap_flip_h);
               void set_debug_box_color(ALLEGRO_COLOR debug_box_color);
               AllegroFlare::FrameAnimation::Book* get_animation_book() const;
               AllegroFlare::Placement2D get_place() const;
               AllegroFlare::Placement2D get_velocity() const;
               std::string get_bitmap_alignment_strategy() const;
               bool get_bitmap_flip_h() const;
               ALLEGRO_COLOR get_debug_box_color() const;
               AllegroFlare::Placement2D &get_place_ref();
               AllegroFlare::Placement2D &get_velocity_ref();
               virtual void update() override;
               void refresh_bitmap();
               virtual void draw() override;
               void set_animation(std::string animation_name="[unset-animation_name]");
               void fit_to_bitmap();
            };
         }
      }
   }
}



