

#include <AllegroFlare/Elements/RollingCredits/RollingCredits.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/Elements/RollingCredits/Sections/Header.hpp>
#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Header.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/ColumnWithLabels.hpp>
#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/ColumnWithLabels.hpp>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{


RollingCredits::RollingCredits(AllegroFlare::FontBin* font_bin, std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections, float surface_width, float surface_height)
   : font_bin(font_bin)
   , sections(sections)
   , surface_width(surface_width)
   , surface_height(surface_height)
   , y_offset(0.0f)
   , section_separator_margin(30.0f)
   , height_calculated(0)
   , initialized(false)
{
}


RollingCredits::~RollingCredits()
{
}


void RollingCredits::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void RollingCredits::set_surface_width(float surface_width)
{
   this->surface_width = surface_width;
}


void RollingCredits::set_surface_height(float surface_height)
{
   this->surface_height = surface_height;
}


void RollingCredits::set_y_offset(float y_offset)
{
   this->y_offset = y_offset;
}


void RollingCredits::set_section_separator_margin(float section_separator_margin)
{
   this->section_separator_margin = section_separator_margin;
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


float RollingCredits::get_y_offset()
{
   return y_offset;
}


float RollingCredits::get_section_separator_margin()
{
   return section_separator_margin;
}


float RollingCredits::get_height_calculated()
{
   return height_calculated;
}


void RollingCredits::initialize()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "RollingCredits" << "::" << "initialize" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   height_calculated = calculate_height();
   initialized = true;
   return;
}

void RollingCredits::set_sections(std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections)
{
   this->sections = sections;
   y_offset = 0;
   if (initialized) height_calculated = calculate_height(); // only refresh the height calculation if the
                                                            // component has already been initialized
   return;
}

float RollingCredits::calculate_height()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "RollingCredits" << "::" << "calculate_height" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "RollingCredits" << "::" << "calculate_height" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   return render_or_calculate_height(true);
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
   render_or_calculate_height(false);
   return;
}

float RollingCredits::render_or_calculate_height(bool only_calculate_height_dont_render)
{
   using namespace AllegroFlare::Elements::RollingCredits;

   float cursor_y = y_offset;
   float this_section_height = 0;
   //float section_separator_margin = 30;
   int section_count = 0;
   int num_sections = sections.size();
   float surface_center = surface_width/2;
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
         renderer.set_x(surface_center);
         renderer.set_y(cursor_y);
         this_section_height = renderer.render(only_calculate_height_dont_render);
      }
      else if (section->is_type("ColumnWithLabels"))
      {
         Sections::ColumnWithLabels *typed_section = static_cast<Sections::ColumnWithLabels *>(section);
         SectionRenderers::ColumnWithLabels renderer(
               font_bin,
               typed_section->get_elements()
            );
         renderer.set_x(surface_center);
         renderer.set_y(cursor_y);
         this_section_height = renderer.render(only_calculate_height_dont_render);
      }
      else
      {
         std::stringstream error_message;
         error_message << "AllegroFlare::Elements::RollingCredits::RollingCredits::render error: "
                       << "Cannot render section of the unknown type \"" << section->get_type() << "\".";
         throw std::runtime_error(error_message.str());
      }

      // increment the y_cursor
      cursor_y += this_section_height;

      section_count++;
      bool at_last_section = (section_count == num_sections);
      if (!at_last_section) cursor_y += section_separator_margin;
   }

   return cursor_y;
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


