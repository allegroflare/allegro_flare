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
      public:
         static constexpr ALLEGRO_COLOR CLEAR_COLOR_EIGENGRAU = ALLEGRO_COLOR{0.086f, 0.086f, 0.114f, 1.0f};
         static constexpr ALLEGRO_COLOR CLEAR_COLOR_NEUTRAL = ALLEGRO_COLOR{0.44, 0.5, 0.56, 1.0};
         static constexpr ALLEGRO_COLOR CLEAR_COLOR_LIGHT = ALLEGRO_COLOR{0.98, 0.94, 0.90, 1.0};
         static constexpr ALLEGRO_COLOR CLEAR_COLOR_DARK = ALLEGRO_COLOR{0.054902f, 0.105882f, 0.176476f, 1.0};
         static constexpr char* DEFAULT_FONT_NAME = (char*)"Inter-Regular.ttf";

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
         std::string get_data_path();
         std::string get_data_folder_path();
         virtual void TearDown() override;
         ALLEGRO_FONT* get_any_font(int size=-30);
         ALLEGRO_FONT* get_small_font(int size=-20);
         ALLEGRO_FONT* get_user_prompt_font();
         ALLEGRO_FONT* get_specific_font(std::string font_name="[unset-font_name]", int size=-20);
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
         void draw_crosshair_blue(float x=0.0f, float y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{0, 0, 1, 1}, float size=100.0f);
         void draw_horizontal_crosshair(float x=0.0f, float y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 0, 0, 1}, float size_v=30.0f, float size_h=600.0f);
         void draw_vertical_crosshair(float x=0.0f, float y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 0, 0, 1}, float size_v=600.0f, float size_h=30.0f);
         void draw_rectangle(float x=0.0f, float y=0.0f, float width=160.0f, float height=90.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 0, 0, 1}, float size=100.0f);
         bool test_name_indicates_it_wants_a_screenshot();
         void clear_display();
         void clear();
         void clear_dark();
         void clear_neutral();
         void clear_light();
         void clear_transparent();
         bool test_name_has_prefix_token(std::string possible_prefix_token="[unset-possible_prefix_token]");
         void capture_screenshot(std::string base_filename="WithAllegroRenderingFixture-screenshot.png");
         void save_bitmap_to_test_snapshots_folder(std::string base_filename="WithAllegroRenderingFixture-test_bitmap.png", ALLEGRO_BITMAP* bitmap=nullptr);
      };
   }
}



