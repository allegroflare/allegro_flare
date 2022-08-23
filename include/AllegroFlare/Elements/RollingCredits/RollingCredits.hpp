#pragma once


#include <AllegroFlare/Elements/RollingCredits/Sections/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace RollingCredits
      {
         class RollingCredits
         {
         private:
            AllegroFlare::FontBin* font_bin;
            std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections;
            float y_offset;
            float surface_width;
            float surface_height;

         public:
            RollingCredits(AllegroFlare::FontBin* font_bin=nullptr, std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections={}, float y_offset=0.0f, float surface_width=1920, float surface_height=1080);
            ~RollingCredits();

            void set_y_offset(float y_offset);
            void set_surface_width(float surface_width);
            void set_surface_height(float surface_height);
            std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> get_sections();
            float get_y_offset();
            float get_surface_width();
            float get_surface_height();
            void set_sections(std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections={});
            float render();
            ALLEGRO_FONT* obtain_font();
         };
      }
   }
}



