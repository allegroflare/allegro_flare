#pragma once


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
               ALLEGRO_COLOR debug_box_color;
               static void assign_alignment_strategy_values(AllegroFlare::Placement2D* parent_placement=nullptr, ALLEGRO_BITMAP* bitmap=nullptr, float* bitmap_x=nullptr, float* bitmap_y=nullptr, float* bitmap_align_x=nullptr, float* bitmap_align_y=nullptr, std::string bitmap_alignment_strategy="centered");

            protected:


            public:
               Basic2D();
               virtual ~Basic2D();

               void set_place(AllegroFlare::Placement2D place);
               void set_velocity(AllegroFlare::Placement2D velocity);
               void set_bitmap(ALLEGRO_BITMAP* bitmap);
               void set_bitmap_placement(AllegroFlare::Placement2D bitmap_placement);
               void set_bitmap_alignment_strategy(std::string bitmap_alignment_strategy);
               void set_bitmap_flip_h(bool bitmap_flip_h);
               void set_debug_box_color(ALLEGRO_COLOR debug_box_color);
               AllegroFlare::Placement2D get_place() const;
               AllegroFlare::Placement2D get_velocity() const;
               ALLEGRO_BITMAP* get_bitmap() const;
               AllegroFlare::Placement2D get_bitmap_placement() const;
               std::string get_bitmap_alignment_strategy() const;
               bool get_bitmap_flip_h() const;
               ALLEGRO_COLOR get_debug_box_color() const;
               AllegroFlare::Placement2D &get_place_ref();
               AllegroFlare::Placement2D &get_velocity_ref();
               AllegroFlare::Placement2D &get_bitmap_placement_ref();
               virtual void update() override;
               virtual void draw() override;
               void fit_to_bitmap();
            };
         }
      }
   }
}



