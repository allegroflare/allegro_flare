

#include <AllegroFlare/Elements/ChapterSelect/PaginationBar.hpp>

#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace ChapterSelect
{


PaginationBar::PaginationBar(std::vector<bool> elements, int cursor_position, ALLEGRO_COLOR fill_color_reached, ALLEGRO_COLOR fill_color_unreached, ALLEGRO_COLOR cursor_stroke_line_color, float cursor_stroke_line_thickness, float bar_width, float bar_spacing, float bar_height, float bar_stroke_thickness)
   : AllegroFlare::Elements::Base()
   , elements(elements)
   , cursor_position(cursor_position)
   , fill_color_reached(fill_color_reached)
   , fill_color_unreached(fill_color_unreached)
   , cursor_stroke_line_color(cursor_stroke_line_color)
   , cursor_stroke_line_thickness(cursor_stroke_line_thickness)
   , bar_width(bar_width)
   , bar_spacing(bar_spacing)
   , bar_height(bar_height)
   , bar_stroke_thickness(bar_stroke_thickness)
{
}


PaginationBar::~PaginationBar()
{
}


void PaginationBar::set_elements(std::vector<bool> elements)
{
   this->elements = elements;
}


void PaginationBar::set_cursor_position(int cursor_position)
{
   this->cursor_position = cursor_position;
}


void PaginationBar::set_fill_color_reached(ALLEGRO_COLOR fill_color_reached)
{
   this->fill_color_reached = fill_color_reached;
}


void PaginationBar::set_fill_color_unreached(ALLEGRO_COLOR fill_color_unreached)
{
   this->fill_color_unreached = fill_color_unreached;
}


void PaginationBar::set_cursor_stroke_line_color(ALLEGRO_COLOR cursor_stroke_line_color)
{
   this->cursor_stroke_line_color = cursor_stroke_line_color;
}


void PaginationBar::set_cursor_stroke_line_thickness(float cursor_stroke_line_thickness)
{
   this->cursor_stroke_line_thickness = cursor_stroke_line_thickness;
}


void PaginationBar::set_bar_width(float bar_width)
{
   this->bar_width = bar_width;
}


void PaginationBar::set_bar_spacing(float bar_spacing)
{
   this->bar_spacing = bar_spacing;
}


void PaginationBar::set_bar_height(float bar_height)
{
   this->bar_height = bar_height;
}


void PaginationBar::set_bar_stroke_thickness(float bar_stroke_thickness)
{
   this->bar_stroke_thickness = bar_stroke_thickness;
}


std::vector<bool> PaginationBar::get_elements() const
{
   return elements;
}


int PaginationBar::get_cursor_position() const
{
   return cursor_position;
}


ALLEGRO_COLOR PaginationBar::get_fill_color_reached() const
{
   return fill_color_reached;
}


ALLEGRO_COLOR PaginationBar::get_fill_color_unreached() const
{
   return fill_color_unreached;
}


ALLEGRO_COLOR PaginationBar::get_cursor_stroke_line_color() const
{
   return cursor_stroke_line_color;
}


float PaginationBar::get_cursor_stroke_line_thickness() const
{
   return cursor_stroke_line_thickness;
}


float PaginationBar::get_bar_width() const
{
   return bar_width;
}


float PaginationBar::get_bar_spacing() const
{
   return bar_spacing;
}


float PaginationBar::get_bar_height() const
{
   return bar_height;
}


float PaginationBar::get_bar_stroke_thickness() const
{
   return bar_stroke_thickness;
}


void PaginationBar::update()
{
   return;
}

void PaginationBar::set_element_at(int position, bool value)
{
   if (!((position >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::PaginationBar::set_element_at]: error: guard \"(position >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::PaginationBar::set_element_at]: error: guard \"(position >= 0)\" not met");
   }
   if (!((position < elements.size())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::PaginationBar::set_element_at]: error: guard \"(position < elements.size())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::PaginationBar::set_element_at]: error: guard \"(position < elements.size())\" not met");
   }
   elements[position] = value;
   return;
}

void PaginationBar::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::PaginationBar::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::PaginationBar::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::PaginationBar::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::PaginationBar::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   float h_thickness = bar_stroke_thickness * 0.5;

   get_placement_ref().start_transform();

   // TODO: This could be optimized to a single set of vertexes and a single draw call
   int i = 0;
   for (auto element : elements)
   {
      bool reached = false;
      if (element == true) reached = true;

      al_draw_filled_rectangle(
         i*bar_spacing,
         0,
         i*bar_spacing+bar_width,
         bar_height,
         reached ? fill_color_reached : fill_color_unreached
      );

      if (i == cursor_position)
      {
         float cursor_padding_x = 8;
         float cursor_padding_y = 8;

         al_draw_rectangle(
            i*bar_spacing - cursor_padding_x,
            0 - cursor_padding_y,
            i*bar_spacing+bar_width + cursor_padding_x,
            bar_height + cursor_padding_y,
            cursor_stroke_line_color,
            cursor_stroke_line_thickness
         );
      }

      i++;
   }
   get_placement_ref().restore_transform();
   return;
}

void PaginationBar::fit_placement_width_and_height()
{
   get_placement_ref().size = { calculate_width(), bar_height };
   return;
}

float PaginationBar::calculate_width()
{
   if (get_num_elements() <= 0) return 0;
   // TODO: modify this so that it is coupled with render
   // TODO: add "fit_width" and "fit_height" functions to set the width and height of this Elements::Base dimensions
   return (get_num_elements() - 1)*bar_spacing+bar_width;
}

int PaginationBar::get_num_elements()
{
   return elements.size();
}


} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


