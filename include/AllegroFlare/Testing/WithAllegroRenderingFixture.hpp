#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro_flare/placement2d.h>
#include <gtest/gtest.h>


namespace AllegroFlare
{
   namespace Testing
   {
      class WithAllegroRenderingFixture : public ::testing::Test
      {
      private:
         ALLEGRO_DISPLAY* display;
         AllegroFlare::FontBin font_bin;
         AllegroFlare::BitmapBin bitmap_bin;

      public:
         WithAllegroRenderingFixture();
         virtual ~WithAllegroRenderingFixture();

         ALLEGRO_DISPLAY* get_display();
         AllegroFlare::FontBin &get_font_bin_ref();
         AllegroFlare::BitmapBin &get_bitmap_bin_ref();
         virtual void SetUp() override;
         virtual void TearDown() override;
         ALLEGRO_FONT* get_any_font();
         allegro_flare::placement2d build_centered_placement(float width=0.0f, float height=0.0f);
      };
   }
}



