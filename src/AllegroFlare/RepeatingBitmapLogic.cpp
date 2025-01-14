

#include <AllegroFlare/RepeatingBitmapLogic.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


RepeatingBitmapLogic::RepeatingBitmapLogic(ALLEGRO_BITMAP* bitmap, int column_start, int row_start, int column_end, int row_end, float loop_width, float loop_height, float offset_x, float offset_y, float scroll_rate_x, float scroll_rate_y, AllegroFlare::Placement2D placement)
   : bitmap(bitmap)
   , column_start(column_start)
   , row_start(row_start)
   , column_end(column_end)
   , row_end(row_end)
   , loop_width(loop_width)
   , loop_height(loop_height)
   , offset_x(offset_x)
   , offset_y(offset_y)
   , scroll_rate_x(scroll_rate_x)
   , scroll_rate_y(scroll_rate_y)
   , placement(placement)
{
}


RepeatingBitmapLogic::~RepeatingBitmapLogic()
{
}


void RepeatingBitmapLogic::set_bitmap(ALLEGRO_BITMAP* bitmap)
{
   this->bitmap = bitmap;
}


void RepeatingBitmapLogic::set_column_start(int column_start)
{
   this->column_start = column_start;
}


void RepeatingBitmapLogic::set_row_start(int row_start)
{
   this->row_start = row_start;
}


void RepeatingBitmapLogic::set_column_end(int column_end)
{
   this->column_end = column_end;
}


void RepeatingBitmapLogic::set_row_end(int row_end)
{
   this->row_end = row_end;
}


void RepeatingBitmapLogic::set_loop_width(float loop_width)
{
   this->loop_width = loop_width;
}


void RepeatingBitmapLogic::set_loop_height(float loop_height)
{
   this->loop_height = loop_height;
}


void RepeatingBitmapLogic::set_offset_x(float offset_x)
{
   this->offset_x = offset_x;
}


void RepeatingBitmapLogic::set_offset_y(float offset_y)
{
   this->offset_y = offset_y;
}


void RepeatingBitmapLogic::set_scroll_rate_x(float scroll_rate_x)
{
   this->scroll_rate_x = scroll_rate_x;
}


void RepeatingBitmapLogic::set_scroll_rate_y(float scroll_rate_y)
{
   this->scroll_rate_y = scroll_rate_y;
}


void RepeatingBitmapLogic::set_placement(AllegroFlare::Placement2D placement)
{
   this->placement = placement;
}


ALLEGRO_BITMAP* RepeatingBitmapLogic::get_bitmap() const
{
   return bitmap;
}


int RepeatingBitmapLogic::get_column_start() const
{
   return column_start;
}


int RepeatingBitmapLogic::get_row_start() const
{
   return row_start;
}


int RepeatingBitmapLogic::get_column_end() const
{
   return column_end;
}


int RepeatingBitmapLogic::get_row_end() const
{
   return row_end;
}


float RepeatingBitmapLogic::get_loop_width() const
{
   return loop_width;
}


float RepeatingBitmapLogic::get_loop_height() const
{
   return loop_height;
}


float RepeatingBitmapLogic::get_offset_x() const
{
   return offset_x;
}


float RepeatingBitmapLogic::get_offset_y() const
{
   return offset_y;
}


float RepeatingBitmapLogic::get_scroll_rate_x() const
{
   return scroll_rate_x;
}


float RepeatingBitmapLogic::get_scroll_rate_y() const
{
   return scroll_rate_y;
}


AllegroFlare::Placement2D &RepeatingBitmapLogic::get_placement_ref()
{
   return placement;
}


void RepeatingBitmapLogic::fit_rows_and_columns_to_frame(float x1, float y1, float x2, float y2)
{
   // TODO: This needs to take the placement's scale, width, align, etc, into account 

   //float x_alignment_offset = loop_width * placement.align.x;
   //float y_alignment_offset = loop_height * placement.align.y;

   //x1 += x_alignment_offset;
   //y1 += y_alignment_offset;
   //x2 += x_alignment_offset;
   //y2 += y_alignment_offset;

   //x1 *= scroll_rate_x;
   //y1 *= scroll_rate_y;
   //x2 *= scroll_rate_x;
   //x2 *= scroll_rate_y;

   column_start = (int)(x1 / loop_width) - 1;
   row_start = (int)(y1 / loop_height) - 1;
   column_end = (int)(x2 / loop_width);
   row_end = (int)(y2 / loop_height);

   bool show_offset = false;
   //bool show_offset = true;
   if (show_offset)
   {
      column_start += 1;
      row_start += 1;
      column_end -= 1;
      row_end -= 1;
   }

   return;
}

void RepeatingBitmapLogic::fit_loop_width_to_bitmap_width()
{
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RepeatingBitmapLogic::fit_loop_width_to_bitmap_width]: error: guard \"bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RepeatingBitmapLogic::fit_loop_width_to_bitmap_width]: error: guard \"bitmap\" not met");
   }
   // TODO: Test this method
   loop_width = al_get_bitmap_width(bitmap);
   return;
}

void RepeatingBitmapLogic::fit_loop_height_to_bitmap_height()
{
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RepeatingBitmapLogic::fit_loop_height_to_bitmap_height]: error: guard \"bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RepeatingBitmapLogic::fit_loop_height_to_bitmap_height]: error: guard \"bitmap\" not met");
   }
   // TODO: Test this method
   loop_height = al_get_bitmap_height(bitmap);
   return;
}

void RepeatingBitmapLogic::fit_placement_width_to_bitamp_width()
{
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RepeatingBitmapLogic::fit_placement_width_to_bitamp_width]: error: guard \"bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RepeatingBitmapLogic::fit_placement_width_to_bitamp_width]: error: guard \"bitmap\" not met");
   }
   // TODO: Test this method
   placement.size.x = al_get_bitmap_width(bitmap);
   return;
}

void RepeatingBitmapLogic::fit_placement_height_to_bitamp_height()
{
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RepeatingBitmapLogic::fit_placement_height_to_bitamp_height]: error: guard \"bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RepeatingBitmapLogic::fit_placement_height_to_bitamp_height]: error: guard \"bitmap\" not met");
   }
   // TODO: Test this method
   placement.size.y = al_get_bitmap_height(bitmap);
   return;
}

void RepeatingBitmapLogic::fit_placement_dimensions_to_bitmap_dimensions()
{
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RepeatingBitmapLogic::fit_placement_dimensions_to_bitmap_dimensions]: error: guard \"bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RepeatingBitmapLogic::fit_placement_dimensions_to_bitmap_dimensions]: error: guard \"bitmap\" not met");
   }
   // TODO: Test this method
   fit_placement_width_to_bitamp_width();
   fit_placement_height_to_bitamp_height();
   return;
}

void RepeatingBitmapLogic::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RepeatingBitmapLogic::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RepeatingBitmapLogic::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RepeatingBitmapLogic::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RepeatingBitmapLogic::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RepeatingBitmapLogic::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RepeatingBitmapLogic::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   //float orientation
   return;
}

void RepeatingBitmapLogic::draw_repeating_rows_and_columns()
{
   AllegroFlare::Placement2D looping_transform;
   for (int row=row_start; row<=row_end; row++)
   {
      for (int column=column_start; column<=column_end; column++)
      {
         looping_transform.position.x = (loop_width * column) + offset_x;
         looping_transform.position.y = (loop_height * row) + offset_y;
         looping_transform.start_transform();
         placement.start_transform();
         al_draw_bitmap(bitmap, 0, 0, 0);
         placement.restore_transform();
         looping_transform.restore_transform();
      }
   }
   return;
}


} // namespace AllegroFlare


