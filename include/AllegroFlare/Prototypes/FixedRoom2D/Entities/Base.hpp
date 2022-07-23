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
               virtual void render();
               void update();
               void on_cursor_enter();
               void on_cursor_leave();
               void on_cursor_interact();
            };
         }
      }
   }
}



