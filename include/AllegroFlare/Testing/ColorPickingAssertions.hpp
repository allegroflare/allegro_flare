#pragma once


#include <AllegroFlare/Testing/Comparison/ALLEGRO_COLOR.hpp>


#define EXPECT_PICKED_COLOR_EQ(expected_ALLEGRO_COLOR, source_ALLEGRO_BITMAP, pixel_x, pixel_y) \
   { \
      ALLEGRO_COLOR actual_ALLEGRO_COLOR = al_get_pixel(source_ALLEGRO_BITMAP, pixel_x, pixel_y); \
      EXPECT_EQ(expected_ALLEGRO_COLOR, actual_ALLEGRO_COLOR) << "Color at (" << pixel_x << ", " << pixel_y << ")" \
      "does not match"; \
   }

#define ASSERT_PICKED_COLOR_EQ(expected_ALLEGRO_COLOR, source_ALLEGRO_BITMAP, pixel_x, pixel_y) \
   { \
      ALLEGRO_COLOR actual_ALLEGRO_COLOR = al_get_pixel(source_ALLEGRO_BITMAP, pixel_x, pixel_y); \
      ASSERT_EQ(expected_ALLEGRO_COLOR, actual_ALLEGRO_COLOR) << "Color at (" << pixel_x << ", " << pixel_y << ")" \
      "does not match"; \
   }


