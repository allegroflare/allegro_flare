

#include <AllegroFlare/MotionComposer/TrackView.hpp>
#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace MotionComposer
{


TrackView::TrackView(AllegroFlare::FontBin* font_bin, AllegroFlare::Timeline::Track* track, float x, float y, float width, float height)
   : font_bin(font_bin)
   , track(track)
   , x(x)
   , y(y)
   , width(width)
   , height(height)
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


AllegroFlare::FontBin* TrackView::get_font_bin()
{
   return font_bin;
}


AllegroFlare::Timeline::Track* TrackView::get_track()
{
   return track;
}


float TrackView::get_x()
{
   return x;
}


float TrackView::get_y()
{
   return y;
}


float TrackView::get_width()
{
   return width;
}


float TrackView::get_height()
{
   return height;
}


void TrackView::render()
{
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "TrackView" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "TrackView" << "::" << "render" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(track))
      {
         std::stringstream error_message;
         error_message << "TrackView" << "::" << "render" << ": error: " << "guard \"track\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_FONT *icon_font = obtain_icon_font();
   int count = 0;

   ALLEGRO_COLOR backfill_color = ALLEGRO_COLOR{0.2, 0.205, 0.21, 1.0};
   ALLEGRO_COLOR line_color = ALLEGRO_COLOR{0.1, 0.1, 0.1, 0.1};

   al_draw_filled_rectangle(x, y, width, height, backfill_color);
   float x_scale = 100;

   for (auto &keyframe : track->get_keyframes())
   {
      float keyframe_x = keyframe->time * x_scale;

      al_draw_line(keyframe_x, y, keyframe_x, y+height, line_color, 1.0);

      int32_t diamond = 0xf219;
      ALLEGRO_COLOR color = AllegroFlare::Color::DeepSkyBlue;
      //draw_centered_unicode_character(icon_font, color, x+keyframe_x, y+keyframe_y, diamond, 0);
      count++;
   }
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
         error_message << "TrackView" << "::" << "obtain_icon_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("fa-solid-900.ttf -30");
}

ALLEGRO_FONT* TrackView::obtain_track_values_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "TrackView" << "::" << "obtain_track_values_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Inter-Medium.ttf -20");
}
} // namespace MotionComposer
} // namespace AllegroFlare


