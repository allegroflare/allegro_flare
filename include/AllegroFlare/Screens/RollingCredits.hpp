#pragma once


#include <AllegroFlare/Elements/RollingCredits/RollingCredits.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <vector>


namespace AllegroFlare
{
   namespace Screens
   {
      class RollingCredits : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits_component;
         float surface_width;
         float surface_height;
         float y_offset;
         float y_speed;
         bool initialized;

      public:
         RollingCredits(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits_component={}, float surface_width=1920, float surface_height=1080);
         virtual ~RollingCredits();

         void set_surface_width(float surface_width);
         void set_surface_height(float surface_height);
         void set_y_offset(float y_offset);
         void set_y_speed(float y_speed);
         AllegroFlare::Elements::RollingCredits::RollingCredits get_rolling_credits_component();
         float get_surface_width();
         float get_surface_height();
         float get_y_offset();
         float get_y_speed();
         AllegroFlare::Elements::RollingCredits::RollingCredits &get_rolling_credits_component_ref();
         float &get_y_offset_ref();
         float &get_y_speed_ref();
         virtual void on_activate() override;
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_sections(std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections={});
         void initialize();
         void update();
         void render();
         virtual void primary_timer_func() override;
      };
   }
}



