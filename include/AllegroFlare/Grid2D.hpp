#pragma once




#include <vector>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Vec2D.hpp>




//"If I hadn't tried, the cost would have been my soul." - Kirk




namespace AllegroFlare
{
   class Grid2D
   {
   protected:
      std::vector<float> horizontal_guide;
      std::vector<float> vertical_guide;

   public:
      Grid2D();
      ~Grid2D();

      void add_horizontal_guide(float x);
      void add_vertical_guide(float y);

      float get_max_horizontal_guide();
      float get_max_vertical_guide();
      float get_min_horizontal_guide();
      float get_min_vertical_guide();

      int get_closest_horizontal_guide_index(float x, float threshold = 15);
      int get_closest_vertical_guide_index(float y, float threshold = 15);

      float get_horizontal_guide_pos(int index);
      float get_vertical_guide_pos(int index);

      AllegroFlare::vec2d get_guide_pos(int x_index, int y_index);

      AllegroFlare::vec2d get_closest_coordinates(float x, float y, float threshold = 15);
      AllegroFlare::vec2d get_closest_left_coordinate(float x, float y);

      int get_closest_coordinate_index_to_the_left(float x); // maybe rename these two to something nicer, also returns -1 if not found
      int get_closest_coordinate_index_above(float y);

      void draw_guides(ALLEGRO_COLOR color=AllegroFlare::color::black);
      void draw_guide_numbers(ALLEGRO_FONT *font, float padding=10, ALLEGRO_COLOR color=AllegroFlare::color::black);
   };
}



