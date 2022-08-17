

#include <AllegroFlare/MotionComposer/TrackView.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace MotionComposer
{


TrackView::TrackView()
   : font_bin(nullptr)
   , track(nullptr)
{
}


TrackView::~TrackView()
{
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
   //std::vector<AllegroFlare::Timeline::Keyframe *> get_keyframes();
   for (auto &keyframe : track->get_keyframes())
   {
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


