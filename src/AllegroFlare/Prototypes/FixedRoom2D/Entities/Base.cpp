

#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{
namespace Entities
{


Base::Base(ALLEGRO_BITMAP* bitmap, AllegroFlare::Placement2D placement, std::string on_cursor_interact_script_name)
   : AllegroFlare::ElementID()
   , bitmap(bitmap)
   , placement(placement)
   , on_cursor_interact_script_name(on_cursor_interact_script_name)
   , cursor_is_over(false)
   , cursor_entered_at(0.0f)
   , cursor_exited_at(0.0f)
   , cursor_insights_are_hidden(false)
   , show_hover_as_hue_change(false)
   , hidden(false)
{
}


Base::~Base()
{
}


void Base::set_bitmap(ALLEGRO_BITMAP* bitmap)
{
   this->bitmap = bitmap;
}


void Base::set_placement(AllegroFlare::Placement2D placement)
{
   this->placement = placement;
}


void Base::set_on_cursor_interact_script_name(std::string on_cursor_interact_script_name)
{
   this->on_cursor_interact_script_name = on_cursor_interact_script_name;
}


void Base::set_cursor_insights_are_hidden(bool cursor_insights_are_hidden)
{
   this->cursor_insights_are_hidden = cursor_insights_are_hidden;
}


void Base::set_show_hover_as_hue_change(bool show_hover_as_hue_change)
{
   this->show_hover_as_hue_change = show_hover_as_hue_change;
}


void Base::set_hidden(bool hidden)
{
   this->hidden = hidden;
}


ALLEGRO_BITMAP* Base::get_bitmap() const
{
   return bitmap;
}


AllegroFlare::Placement2D Base::get_placement() const
{
   return placement;
}


std::string Base::get_on_cursor_interact_script_name() const
{
   return on_cursor_interact_script_name;
}


bool Base::get_cursor_is_over() const
{
   return cursor_is_over;
}


float Base::get_cursor_entered_at() const
{
   return cursor_entered_at;
}


float Base::get_cursor_exited_at() const
{
   return cursor_exited_at;
}


bool Base::get_cursor_insights_are_hidden() const
{
   return cursor_insights_are_hidden;
}


bool Base::get_show_hover_as_hue_change() const
{
   return show_hover_as_hue_change;
}


bool Base::get_hidden() const
{
   return hidden;
}


AllegroFlare::Placement2D &Base::get_placement_ref()
{
   return placement;
}


void Base::render()
{
   if (!bitmap || get_hidden()) return;

   placement.start_transform();

   if (show_hover_as_hue_change && cursor_is_over)
   {
      al_draw_tinted_bitmap(bitmap, ALLEGRO_COLOR{0.12, 0.56, 1.0, 1.0}, 0, 0, 0);
   }
   else
   {
      al_draw_bitmap(bitmap, 0, 0, 0);
   }

   placement.restore_transform();
   return;
}

void Base::update()
{
   return;
}

void Base::on_cursor_enter()
{
   cursor_is_over = true;
   cursor_entered_at = al_get_time();
   cursor_exited_at = 0;
   return;
}

void Base::on_cursor_leave()
{
   cursor_is_over = false;
   cursor_entered_at = 0;
   cursor_exited_at = al_get_time();
   return;
}


} // namespace Entities
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


