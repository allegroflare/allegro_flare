

#include <AllegroFlare/MotionComposer/TrackView.hpp>

#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace MotionComposer
{


TrackView::TrackView(AllegroFlare::FontBin* font_bin, AllegroFlare::Timeline::Track* track, float x, float y, float width, float height, float value_min, float value_max, int selection_cursor_x)
   : font_bin(font_bin)
   , track(track)
   , x(x)
   , y(y)
   , width(width)
   , height(height)
   , value_min(value_min)
   , value_max(value_max)
   , selection_cursor_x(selection_cursor_x)
   , icon_font_size(-22)
{
}


TrackView::~TrackView()
{
}


void TrackView::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void TrackView::set_track(AllegroFlare::Timeline::Track* track)
{
   this->track = track;
}


void TrackView::set_x(float x)
{
   this->x = x;
}


void TrackView::set_y(float y)
{
   this->y = y;
}


void TrackView::set_width(float width)
{
   this->width = width;
}


void TrackView::set_height(float height)
{
   this->height = height;
}


void TrackView::set_value_min(float value_min)
{
   this->value_min = value_min;
}


void TrackView::set_value_max(float value_max)
{
   this->value_max = value_max;
}


void TrackView::set_selection_cursor_x(int selection_cursor_x)
{
   this->selection_cursor_x = selection_cursor_x;
}


void TrackView::set_icon_font_size(int icon_font_size)
{
   this->icon_font_size = icon_font_size;
}


AllegroFlare::FontBin* TrackView::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::Timeline::Track* TrackView::get_track() const
{
   return track;
}


float TrackView::get_x() const
{
   return x;
}


float TrackView::get_y() const
{
   return y;
}


float TrackView::get_width() const
{
   return width;
}


float TrackView::get_height() const
{
   return height;
}


float TrackView::get_value_min() const
{
   return value_min;
}


float TrackView::get_value_max() const
{
   return value_max;
}


int TrackView::get_selection_cursor_x() const
{
   return selection_cursor_x;
}


int TrackView::get_icon_font_size() const
{
   return icon_font_size;
}


void TrackView::render()
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionComposer::TrackView::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionComposer::TrackView::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionComposer::TrackView::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionComposer::TrackView::render]: error: guard \"font_bin\" not met");
   }
   if (!(track))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionComposer::TrackView::render]: error: guard \"track\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionComposer::TrackView::render]: error: guard \"track\" not met");
   }
   ALLEGRO_COLOR backfill_color = ALLEGRO_COLOR{0.2, 0.205, 0.21, 1.0};
   ALLEGRO_COLOR line_color = ALLEGRO_COLOR{0.1, 0.1, 0.1, 0.1};

   al_draw_filled_rectangle(x, y, width, height, backfill_color);
   float x_scale = 100;
   float y_scale = height;

   int count = 0;
   for (auto &keyframe : track->get_keyframes())
   {
      float capped_normalized_y = keyframe->val;
      float keyframe_x = keyframe->time * x_scale;
      float keyframe_y = capped_normalized_y * y_scale;

      // draw a line demarcating where keyframes are
      al_draw_line(keyframe_x, y, keyframe_x, y+height, line_color, 1.0);

      // draw a graphic on the node
      if (count == selection_cursor_x) draw_selected_node_icon(x+keyframe_x, y+keyframe_y);
      else draw_node_icon(x+keyframe_x, y+keyframe_y);

      // increment our count
      count++;
   }
   return;
}

void TrackView::draw_selected_node_icon(float x, float y)
{
   ALLEGRO_FONT *bigger_icon_font = obtain_bigger_icon_font();
   ALLEGRO_FONT *icon_font = obtain_icon_font();
   int32_t diamond = 0xf219;
   ALLEGRO_COLOR bigger_color = AllegroFlare::Color::DeepSkyBlue;
   ALLEGRO_COLOR color = AllegroFlare::Color::Eigengrau;
   draw_centered_unicode_character(bigger_icon_font, bigger_color, x, y, diamond, 0);
   draw_centered_unicode_character(icon_font, color, x, y, diamond, 0);
   return;
}

void TrackView::draw_node_icon(float x, float y)
{
   ALLEGRO_FONT *icon_font = obtain_icon_font();
   int32_t diamond = 0xf219;
   ALLEGRO_COLOR color = AllegroFlare::Color::DeepSkyBlue;
   draw_centered_unicode_character(icon_font, color, x, y, diamond, 0);
   return;
}

void TrackView::draw_centered_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, int x, int y, uint32_t icon, int flags)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   float width = al_get_ustr_width(font, ustr);
   float height = al_get_font_line_height(font);
   al_draw_ustr(font, color, x-width*0.5, y-height*0.5, flags, ustr);
   return;
}

ALLEGRO_FONT* TrackView::obtain_icon_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionComposer::TrackView::obtain_icon_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionComposer::TrackView::obtain_icon_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream ss;
   ss << "fa-solid-900.ttf " << icon_font_size;
   return font_bin->auto_get(ss.str());
}

ALLEGRO_FONT* TrackView::obtain_bigger_icon_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionComposer::TrackView::obtain_bigger_icon_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionComposer::TrackView::obtain_bigger_icon_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream ss;
   ss << "fa-solid-900.ttf " << icon_font_size - 8;
   return font_bin->auto_get(ss.str());
}

ALLEGRO_FONT* TrackView::obtain_track_values_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionComposer::TrackView::obtain_track_values_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionComposer::TrackView::obtain_track_values_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -20");
}


} // namespace MotionComposer
} // namespace AllegroFlare


