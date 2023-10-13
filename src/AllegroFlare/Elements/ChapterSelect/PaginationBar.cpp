

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


PaginationBar::PaginationBar(int max, int value, ALLEGRO_COLOR fill_color_reached, ALLEGRO_COLOR fill_color_unreached, float bar_width, float bar_spacing, float bar_height, float bar_stroke_thickness)
   : AllegroFlare::Elements::Base()
   , max(max)
   , value(value)
   , fill_color_reached(fill_color_reached)
   , fill_color_unreached(fill_color_unreached)
   , bar_width(bar_width)
   , bar_spacing(bar_spacing)
   , bar_height(bar_height)
   , bar_stroke_thickness(bar_stroke_thickness)
{
}


PaginationBar::~PaginationBar()
{
}


void PaginationBar::set_max(int max)
{
   this->max = max;
}


void PaginationBar::set_value(int value)
{
   this->value = value;
}


void PaginationBar::set_fill_color_reached(ALLEGRO_COLOR fill_color_reached)
{
   this->fill_color_reached = fill_color_reached;
}


void PaginationBar::set_fill_color_unreached(ALLEGRO_COLOR fill_color_unreached)
{
   this->fill_color_unreached = fill_color_unreached;
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


int PaginationBar::get_max() const
{
   return max;
}


int PaginationBar::get_value() const
{
   return value;
}


ALLEGRO_COLOR PaginationBar::get_fill_color_reached() const
{
   return fill_color_reached;
}


ALLEGRO_COLOR PaginationBar::get_fill_color_unreached() const
{
   return fill_color_unreached;
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


void PaginationBar::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[PaginationBar::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PaginationBar::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PaginationBar::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PaginationBar::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   float h_thickness = bar_stroke_thickness * 0.5;
   //ALLEGRO_COLOR outline_color = ALLEGRO_COLOR{1, 1, 1, 1};

   get_placement_ref().start_transform();

   // TODO: This could be optimized to a single set of vertexes and a single draw call
   for (int i=0; i<max; i++)
   {
      bool reached = false;
      if (i <= (value - 1)) reached = true;
      //{
      al_draw_filled_rectangle(
         i*bar_spacing,
         0,
         i*bar_spacing+bar_width,
         bar_height,
         reached ? fill_color_reached : fill_color_unreached
      );
      //}
      //else
      //{
         //al_draw_filled_rectangle(
               //i*bar_spacing + h_thickness,
               //0 + h_thickness,
               //i*bar_spacing+bar_width - h_thickness,
               //bar_height - h_thickness,
               //empty_box_fill_color
               ////bar_stroke_thickness
            //);
      //}
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
   if (max <= 0) return 0;
   // TODO: modify this so that it is coupled with render
   // TODO: add "fit_width" and "fit_height" functions to set the width and height of this Elements::Base dimensions
   return (max - 1)*bar_spacing+bar_width;
}


} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


