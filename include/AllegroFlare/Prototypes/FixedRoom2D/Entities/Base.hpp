#pragma once


#include <AllegroFlare/ElementID.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         namespace Entities
         {
            class Base : public AllegroFlare::ElementID
            {
            private:
               ALLEGRO_BITMAP* bitmap;
               AllegroFlare::Placement2D placement;
               bool cursor_is_over;

            public:
               Base(ALLEGRO_BITMAP* bitmap=nullptr, AllegroFlare::Placement2D placement={});
               virtual ~Base();

               void set_bitmap(ALLEGRO_BITMAP* bitmap);
               void set_placement(AllegroFlare::Placement2D placement);
               void set_cursor_is_over(bool cursor_is_over);
               ALLEGRO_BITMAP* get_bitmap();
               AllegroFlare::Placement2D get_placement();
               bool get_cursor_is_over();
               AllegroFlare::Placement2D &get_placement_ref();
               virtual void render();
               virtual void update();
               virtual void on_cursor_enter();
               virtual void on_cursor_leave();
               virtual void on_cursor_interact();
            };
         }
      }
   }
}



