

#include <AllegroFlare/MotionComposer/TrackView.hpp>
#include <AllegroFlare/Color.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace MotionComposer
{


TrackView::TrackView(AllegroFlare::FontBin* font_bin, AllegroFlare::Timeline::Track* track)
   : font_bin(font_bin)
   , track(track)
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


AllegroFlare::FontBin* TrackView::get_font_bin()
{
   return font_bin;
}


AllegroFlare::Timeline::Track* TrackView::get_track()
{
   return track;
}


void TrackView::render()
{
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
   float track_x = 100;
   float track_y = 100;
   for (auto &keyframe : track->get_keyframes())
   {
      float x_scale = 100;
      float keyframe_x = keyframe->time * x_scale;
      //draw_centered_unicode_character(icon_font, 

      int32_t diamond = 0xf219;
      ALLEGRO_COLOR color = AllegroFlare::Color::DeepSkyBlue;
      draw_centered_unicode_character(icon_font, color, track_x, track_y, diamond, 0);
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
} // namespace MotionComposer
} // namespace AllegroFlare


