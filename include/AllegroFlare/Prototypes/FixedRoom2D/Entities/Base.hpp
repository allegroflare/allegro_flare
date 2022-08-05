#pragma once


#include <AllegroFlare/ElementID.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <string>


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
               std::string on_cursor_interact_script_name;
               bool cursor_is_over;
               float cursor_entered_at;
               float cursor_exited_at;
               bool disable_cursor_insights;

            public:
               Base(ALLEGRO_BITMAP* bitmap=nullptr, AllegroFlare::Placement2D placement={}, std::string on_cursor_interact_script_name="[unset-on_cursor_interact_script_name]");
               virtual ~Base();

               void set_bitmap(ALLEGRO_BITMAP* bitmap);
               void set_placement(AllegroFlare::Placement2D placement);
               void set_on_cursor_interact_script_name(std::string on_cursor_interact_script_name);
               void set_disable_cursor_insights(bool disable_cursor_insights);
               ALLEGRO_BITMAP* get_bitmap();
               AllegroFlare::Placement2D get_placement();
               std::string get_on_cursor_interact_script_name();
               bool get_cursor_is_over();
               float get_cursor_entered_at();
               float get_cursor_exited_at();
               bool get_disable_cursor_insights();
               AllegroFlare::Placement2D &get_placement_ref();
               virtual void render();
               virtual void update();
               virtual void on_cursor_enter();
               virtual void on_cursor_leave();
            };
         }
      }
   }
}



