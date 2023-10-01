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
            float surface_width;
            float surface_height;
            float y_offset;
            float section_separator_margin;
            float height_calculated;
            bool initialized;
            ALLEGRO_FONT* obtain_font();

         protected:


         public:
            RollingCredits(AllegroFlare::FontBin* font_bin=nullptr, std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections={}, float surface_width=1920, float surface_height=1080);
            ~RollingCredits();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_surface_width(float surface_width);
            void set_surface_height(float surface_height);
            void set_y_offset(float y_offset);
            void set_section_separator_margin(float section_separator_margin);
            std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> get_sections() const;
            float get_surface_width() const;
            float get_surface_height() const;
            float get_y_offset() const;
            float get_section_separator_margin() const;
            float get_height_calculated() const;
            void initialize();
            void set_sections(std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections={});
            void append_section(AllegroFlare::Elements::RollingCredits::Sections::Base* section=nullptr);
            void append_sections(std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections_to_append={});
            float calculate_height();
            void render();
            float render_or_calculate_height(bool only_calculate_height_dont_render=false);
         };
      }
   }
}



