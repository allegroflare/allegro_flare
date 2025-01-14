#pragma once


#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   class RepeatingBitmapLogic
   {
   private:
      ALLEGRO_BITMAP* bitmap;
      int column_start;
      int row_start;
      int column_end;
      int row_end;
      float loop_width;
      float loop_height;
      float offset_x;
      float offset_y;
      float scroll_rate_x;
      float scroll_rate_y;
      AllegroFlare::Placement2D placement;

   protected:


   public:
      RepeatingBitmapLogic(ALLEGRO_BITMAP* bitmap=nullptr, int column_start=0, int row_start=0, int column_end=0, int row_end=0, float loop_width=0.0f, float loop_height=0.0f, float offset_x=0.0f, float offset_y=0.0f, float scroll_rate_x=1.0f, float scroll_rate_y=1.0f, AllegroFlare::Placement2D placement={});
      ~RepeatingBitmapLogic();

      void set_bitmap(ALLEGRO_BITMAP* bitmap);
      void set_column_start(int column_start);
      void set_row_start(int row_start);
      void set_column_end(int column_end);
      void set_row_end(int row_end);
      void set_loop_width(float loop_width);
      void set_loop_height(float loop_height);
      void set_offset_x(float offset_x);
      void set_offset_y(float offset_y);
      void set_scroll_rate_x(float scroll_rate_x);
      void set_scroll_rate_y(float scroll_rate_y);
      void set_placement(AllegroFlare::Placement2D placement);
      ALLEGRO_BITMAP* get_bitmap() const;
      int get_column_start() const;
      int get_row_start() const;
      int get_column_end() const;
      int get_row_end() const;
      float get_loop_width() const;
      float get_loop_height() const;
      float get_offset_x() const;
      float get_offset_y() const;
      float get_scroll_rate_x() const;
      float get_scroll_rate_y() const;
      AllegroFlare::Placement2D &get_placement_ref();
      void fit_rows_and_columns_to_frame(float x1=0.0f, float y1=0.0f, float x2=1920.0f, float y2=1080.0f);
      void fit_loop_width_to_bitmap_width();
      void fit_loop_height_to_bitmap_height();
      void fit_placement_width_to_bitamp_width();
      void fit_placement_height_to_bitamp_height();
      void fit_placement_dimensions_to_bitmap_dimensions();
      void render();
      void draw_repeating_rows_and_columns();
   };
}



