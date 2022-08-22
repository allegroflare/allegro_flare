

#include <AllegroFlare/Elements/RollingCredits/RollingCredits.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Header.hpp>
#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Header.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/ColumnWithLabels.hpp>
#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/ColumnWithLabels.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{


RollingCredits::RollingCredits(AllegroFlare::FontBin* font_bin, std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections, float y_offset, float surface_width, float surface_height)
   : font_bin(font_bin)
   , sections(sections)
   , y_offset(y_offset)
   , surface_width(surface_width)
   , surface_height(surface_height)
{
}


RollingCredits::~RollingCredits()
{
}


void RollingCredits::set_surface_width(float surface_width)
{
   this->surface_width = surface_width;
}


void RollingCredits::set_surface_height(float surface_height)
{
   this->surface_height = surface_height;
}


std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> RollingCredits::get_sections()
{
   return sections;
}


float RollingCredits::get_surface_width()
{
   return surface_width;
}


float RollingCredits::get_surface_height()
{
   return surface_height;
}


void RollingCredits::set_sections(std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections)
{
   this->sections = sections;
   y_offset = 0;
   return;
}

void RollingCredits::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "RollingCredits" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "RollingCredits" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   using namespace AllegroFlare::Elements::RollingCredits;

   float cursor_y = 0;
   float this_section_height = 0;
   float section_separator_margin = 30;
   for (auto &section : sections)
   {
      // render the section(s)
      if (section->is_type("Header"))
      {
         Sections::Header *typed_section = static_cast<Sections::Header*>(section);
         SectionRenderers::Header renderer(
               font_bin,
               typed_section->get_text()
            );
         renderer.set_x(surface_width/2);
         renderer.set_y(cursor_y);
         this_section_height = renderer.render();
      }
      else if (section->is_type("ColumnWithLabels"))
      {
         Sections::ColumnWithLabels *typed_section = static_cast<Sections::ColumnWithLabels *>(section);
         SectionRenderers::ColumnWithLabels renderer(
               font_bin,
               typed_section->get_elements()
            );
         renderer.set_x(surface_width/2);
         renderer.set_y(cursor_y);
         this_section_height = renderer.render();
      }
      else
      {
         std::stringstream error_message;
         error_message << "AllegroFlare::Elements::RollingCredits::RollingCredits::render error: "
                       << "Cannot render section of the unknown type \"" << section->get_type() << "\".";
         throw std::runtime_error(error_message.str());
      }

      // increment the y_cursor
      cursor_y += this_section_height + section_separator_margin;
   }
   return;
}

ALLEGRO_FONT* RollingCredits::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "RollingCredits" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Inter-Medium.ftf -32");
}
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


