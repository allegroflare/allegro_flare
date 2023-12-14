#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>


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
         int display_width;
         int display_height;
         int display_samples;
         AllegroFlare::DeploymentEnvironment deployment_environment;
         std::string test_snapshots_folder;
         std::vector<std::string> test_prefix_tokens;
         bool is_setup;

      protected:


      public:
         WithAllegroRenderingFixture();
         virtual ~WithAllegroRenderingFixture();

         ALLEGRO_DISPLAY* get_display() const;
         int get_display_width() const;
         int get_display_height() const;
         int get_display_samples() const;
         AllegroFlare::FontBin &get_font_bin_ref();
         AllegroFlare::BitmapBin &get_bitmap_bin_ref();
         void set_display_samples(int display_samples=4);
         void set_display_width(int display_width=1920);
         void set_display_height(int display_height=1080);
         virtual void SetUp() override;
         std::string get_fixtures_path();
         virtual void TearDown() override;
         ALLEGRO_FONT* get_any_font(int size=-30);
         ALLEGRO_FONT* get_user_prompt_font();
         ALLEGRO_BITMAP* get_display_backbuffer();
         void sleep_for_frame();
         void sleep_for(float length_in_seconds=0.0f);
         std::string get_test_name();
         std::string get_test_suite_name();
         std::vector<std::string> extract_test_prefix_tokens();
         std::string build_full_test_name_str();
         AllegroFlare::Placement2D build_centered_placement(float width=0.0f, float height=0.0f);
         void draw_rulers();
         void draw_crosshair(float x=0.0f, float y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 0, 0, 1}, float size=200.0f);
         void draw_horizontal_crosshair(float x=0.0f, float y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 0, 1}, float size_v=30.0f, float size_h=500.0f);
         bool test_name_indicates_it_wants_a_screenshot();
         void clear_display();
         void clear();
         bool test_name_has_prefix_token(std::string possible_prefix_token="[unset-possible_prefix_token]");
         void capture_screenshot(std::string base_filename="WithAllegroRenderingFixture-screenshot.png");
      };
   }
}



