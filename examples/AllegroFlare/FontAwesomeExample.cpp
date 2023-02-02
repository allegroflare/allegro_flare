

#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/UnicodeFontViewer.hpp>


class FontAwesomeExample : public AllegroFlare::Screens::Base
{
private:
   AllegroFlare::UnicodeFontViewer unicode_font_viewer;

public:
   FontAwesomeExample(AllegroFlare::FontBin *font_bin)
      : AllegroFlare::Screens::Base()
      , unicode_font_viewer(font_bin, "fa-solid-900.ttf", 0xF000) // FontAwesome characters start in the 0xF000 range
   {}

   void primary_timer_func() override
   {
      unicode_font_viewer.render();
   }

   void key_char_func(ALLEGRO_EVENT *ev) override
   {
      switch(ev->keyboard.keycode)
      {
      case ALLEGRO_KEY_RIGHT:
         unicode_font_viewer.next_page();
         break;
      case ALLEGRO_KEY_LEFT:
         unicode_font_viewer.previous_page();
         break;
      }
   }
};


int main(int argc, char **argv)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment(AllegroFlare::DeploymentEnvironment::ENVIRONMENT_DEMO);
   framework.initialize();

   FontAwesomeExample font_awesome_example(&framework.get_font_bin_ref());
   framework.register_and_activate_screen("font_awesome_example", &font_awesome_example);

   framework.run_loop();

   return 0;
}


