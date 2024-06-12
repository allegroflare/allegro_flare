

#include <AllegroFlare/Elements/RollingCredits/RollingCredits.hpp>

#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/ColumnWithLabels.hpp>
#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Header.hpp>
#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/LegalText.hpp>
#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Multicolumn.hpp>
#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Text.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/ColumnWithLabels.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Header.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/LegalText.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Multicolumn.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Spacer.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Text.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


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
   , section_separator_margin(36.0f)
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


std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> RollingCredits::get_sections() const
{
   return sections;
}


float RollingCredits::get_surface_width() const
{
   return surface_width;
}


float RollingCredits::get_surface_height() const
{
   return surface_height;
}


float RollingCredits::get_y_offset() const
{
   return y_offset;
}


float RollingCredits::get_section_separator_margin() const
{
   return section_separator_margin;
}


float RollingCredits::get_height_calculated() const
{
   return height_calculated;
}


void RollingCredits::initialize()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::RollingCredits::RollingCredits::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::RollingCredits::initialize]: error: guard \"font_bin\" not met");
   }
   height_calculated = calculate_height();
   initialized = true;
   return;
}

void RollingCredits::set_sections(std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections)
{
   this->sections = sections;
   y_offset = 0;
   if (initialized) height_calculated = calculate_height();
   return;
}

void RollingCredits::append_section(AllegroFlare::Elements::RollingCredits::Sections::Base* section)
{
   if (!(section))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::RollingCredits::RollingCredits::append_section]: error: guard \"section\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::RollingCredits::append_section]: error: guard \"section\" not met");
   }
   // TODO: Test this method
   sections.push_back(section);
   y_offset = 0;
   if (initialized) height_calculated = calculate_height();
   return;
}

void RollingCredits::append_sections(std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections_to_append)
{
   // TODO: Test this method
   sections.insert(sections.end(), sections_to_append.begin(), sections_to_append.end());
   y_offset = 0;
   if (initialized) height_calculated = calculate_height();
   return;
}

float RollingCredits::calculate_height()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::RollingCredits::RollingCredits::calculate_height]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::RollingCredits::calculate_height]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::RollingCredits::RollingCredits::calculate_height]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::RollingCredits::calculate_height]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   return render_or_calculate_height(true);
}

void RollingCredits::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::RollingCredits::RollingCredits::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::RollingCredits::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::RollingCredits::RollingCredits::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::RollingCredits::render]: error: guard \"al_is_font_addon_initialized()\" not met");
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

         // upcase_titles
         std::string title_text = typed_section->get_text();
         std::transform(title_text.begin(), title_text.end(), title_text.begin(), ::toupper);

         SectionRenderers::Header renderer(
               font_bin,
               title_text
            );
         renderer.set_x(surface_center);
         renderer.set_y(cursor_y);
         renderer.set_font_name("PathwayGothicOne-Regular.ttf");
         renderer.set_font_size(-58);
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
      else if (section->is_type(AllegroFlare::Elements::RollingCredits::Sections::Text::TYPE))
      {
         Sections::Text *typed_section = static_cast<Sections::Text *>(section);
         SectionRenderers::Text renderer(
               font_bin,
               typed_section->get_text(),
               typed_section->get_alignment()
            );
         renderer.set_x(surface_center);
         renderer.set_y(cursor_y);
         this_section_height = renderer.render(only_calculate_height_dont_render);
      }
      else if (section->is_type(AllegroFlare::Elements::RollingCredits::Sections::LegalText::TYPE))
      {
         AllegroFlare::Elements::RollingCredits::Sections::LegalText *as =
            static_cast<AllegroFlare::Elements::RollingCredits::Sections::LegalText*>(section);

         AllegroFlare::Elements::RollingCredits::SectionRenderers::LegalText renderer(
               font_bin,
               as->get_text(),
               as->get_alignment()
            );
         renderer.set_x(surface_center);
         renderer.set_y(cursor_y);
         this_section_height = renderer.render(only_calculate_height_dont_render);
      }
      else if (section->is_type(AllegroFlare::Elements::RollingCredits::Sections::Multicolumn::TYPE))
      {
         AllegroFlare::Elements::RollingCredits::Sections::Multicolumn *as =
            static_cast<AllegroFlare::Elements::RollingCredits::Sections::Multicolumn*>(section);

         AllegroFlare::Elements::RollingCredits::SectionRenderers::Multicolumn renderer(
               font_bin,
               as->get_elements()
            );
         renderer.set_element_alignment("centered");
         renderer.set_x(surface_center);
         renderer.set_y(cursor_y);
         this_section_height = renderer.render(only_calculate_height_dont_render);
      }
      else if (section->is_type(AllegroFlare::Elements::RollingCredits::Sections::Spacer::TYPE))
      {
         AllegroFlare::Elements::RollingCredits::Sections::Spacer *as =
            static_cast<AllegroFlare::Elements::RollingCredits::Sections::Spacer*>(section);
         this_section_height = as->get_height_px();
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
      error_message << "[AllegroFlare::Elements::RollingCredits::RollingCredits::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::RollingCredits::obtain_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ftf -32");
}


} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


