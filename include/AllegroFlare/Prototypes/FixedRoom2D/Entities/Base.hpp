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
               bool cursor_insights_are_hidden;
               bool show_hover_as_hue_change;
               bool hidden;

            public:
               Base(ALLEGRO_BITMAP* bitmap=nullptr, AllegroFlare::Placement2D placement={}, std::string on_cursor_interact_script_name="[unset-on_cursor_interact_script_name]");
               virtual ~Base();

               void set_bitmap(ALLEGRO_BITMAP* bitmap);
               void set_placement(AllegroFlare::Placement2D placement);
               void set_on_cursor_interact_script_name(std::string on_cursor_interact_script_name);
               void set_cursor_insights_are_hidden(bool cursor_insights_are_hidden);
               void set_show_hover_as_hue_change(bool show_hover_as_hue_change);
               void set_hidden(bool hidden);
               ALLEGRO_BITMAP* get_bitmap() const;
               AllegroFlare::Placement2D get_placement() const;
               std::string get_on_cursor_interact_script_name() const;
               bool get_cursor_is_over() const;
               float get_cursor_entered_at() const;
               float get_cursor_exited_at() const;
               bool get_cursor_insights_are_hidden() const;
               bool get_show_hover_as_hue_change() const;
               bool get_hidden() const;
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



