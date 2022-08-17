#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>


#include <AllegroFlare/Timeline/Actor.hpp>
#include <AllegroFlare/Timeline/Track.hpp>
#include <AllegroFlare/Color.hpp>


ALLEGRO_FONT *icon_font = nullptr;


void draw_centered_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, int x, int y, uint32_t icon, int flags)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   float width = al_get_ustr_width(font, ustr);
   float height = al_get_font_line_height(font);
   al_draw_ustr(font, color, x-width*0.5, y-height*0.5, flags, ustr);
   return;
}



class TrackView
{
private:
   AllegroFlare::Timeline::Track *track;
   float width;
   float height;
   float time_start;
   float time_scale;

public:
   TrackView(AllegroFlare::Timeline::Track *track)
      : track(track)
   {};
   void draw()
   {
      float track_x = 0;
      float track_y = 0;

      int count = 0;
      for (auto &keyframe : track->get_keyframes())
      {
         int32_t diamond = 0xf219;
         ALLEGRO_COLOR color = AllegroFlare::Color::DeepSkyBlue;
         draw_centered_unicode_character(icon_font, color, track_x, track_y, diamond, 0);
         count++;
      }
   }
};



class MotionEdit : public AllegroFlare::Screens::Base
{
private:
   std::vector<AllegroFlare::Timeline::Actor*> actors;
public:
   MotionEdit()
      : AllegroFlare::Screens::Base()
   {}
   ~MotionEdit() {}

   virtual void primary_timer_func() override
   {
      for (auto &actor : actors)
      {
         //TrackView track_view(actor);
      }
   }
};



int main(int argc, char **argv)
{
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();

   icon_font = framework.get_font_bin_ref()[""];

   MotionEdit motion_edit;
   framework.register_screen("motion_edit", &motion_edit);
   framework.activate_screen("motion_edit");

   framework.run_loop();
}



