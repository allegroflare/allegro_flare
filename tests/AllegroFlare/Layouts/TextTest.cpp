#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Layouts/Text.hpp>
//#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <AllegroFlare/Generators/LoremIpsumGenerator.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Shaders/FlatColor.hpp>


// TODO: Improve these tests. There are a lot of extra tests, and the tests do not specifically showcase
// text


class AllegroFlare_Layouts_TextTest : public ::testing::Test {};
class AllegroFlare_Layouts_TextTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Layouts_TextTestWithViewer
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   ALLEGRO_COLOR orange = ALLEGRO_COLOR{1.0, 0.65, 0.0, 1.0};
   ALLEGRO_COLOR black = ALLEGRO_COLOR{0.0, 0.0, 0.0, 1.0};
   ALLEGRO_COLOR slate = ALLEGRO_COLOR{0.18, 0.31, 0.31, 1.0};
   ALLEGRO_COLOR firebrick = ALLEGRO_COLOR{0.7, 0.13, 0.13, 1.0};
   ALLEGRO_COLOR eigengrau = ALLEGRO_COLOR{0.1, 0.1, 0.12, 1.0};
   ALLEGRO_COLOR white = ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0};
   ALLEGRO_COLOR background_color = eigengrau;
   ALLEGRO_COLOR foreground_color = white;

   AllegroFlare::Camera2D camera_2d;
   AllegroFlare::Shaders::FlatColor flat_color_shader;
   AllegroFlare::Layouts::Text layout;

   void SetUp()
   {
      AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();

      flat_color_shader.set_color(foreground_color);
      flat_color_shader.set_color_intensity(0.85);
      flat_color_shader.initialize();

      //layout.set_bitmap_bin(&get_bitmap_bin_ref());
      layout.set_font_bin(&get_font_bin_ref());
   }

   void setup_subject(
         std::string tmj_layout_filename,
         std::string atlas_filename, 
         std::map<std::string, std::string> text_data,
         int scale = 2
      )
   { 
      std::string maps_data_path = get_data_path() + "maps/";
      //std::map<std::string, std::string> text_data;
      //{
         //layout.set_tmj_filename(maps_data_path + "reticle_with_flipped_tiles_1-01.tmj");
         //layout.set_prim_mesh_atlas_filename("ascii_glyphs_12x16-08.png");
      //}
      {
         layout.set_tmj_filename(maps_data_path + tmj_layout_filename);
         //layout.set_prim_mesh_atlas_filename("ascii_glyphs_12x16-08.png");
         //layout.set_prim_mesh_atlas_filename(atlas_filename);
      }

      //AllegroFlare::Generators::LoremIpsumGenerator ipsum;
      layout.set_scale(scale); // TODO: Add test that rendering appears as expected under different scales
      layout.initialize();

      layout.set_text_data(text_data);
   }

   void view_subject()
   {
      clear();
      al_clear_to_color(background_color);
      //camera_2d.setup_dimensional_projection(al_get_target_bitmap());
      ALLEGRO_TRANSFORM t;
      al_identity_transform(&t);
      //al_rotate_transform_3d(&t, 0, 1, 0, 0.25);
      al_translate_transform( // TODO: Fix this
         &t,
         1920/2 - layout.get_layout_width()/2,
         1080/2 - layout.get_layout_height()/2
      );
      al_use_transform(&t);

      //flat_color_shader.activate();
      layout.render();
      //flat_color_shader.deactivate();

      al_flip_display();
   }
};


TEST_F(AllegroFlare_Layouts_TextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Layouts::Text layout;
}


/*

TEST_F(Layouts_TextTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   std::string maps_data_path = get_data_path() + "maps/";
   AllegroFlare::Layouts::Text layout(&get_font_bin_ref());
   layout.set_tmj_filename(maps_data_path + "layout_1-04.tmj");
   layout.initialize();

   layout.set_text_data({
      { "primary_label", "SEARCHING..." },
      { "nav_bar",       "v0.14.715n" },
   });

   clear();
   layout.render();

   al_flip_display();
   //sleep_for(1);
}


TEST_F(Layouts_TextTestWithAllegroRenderingFixture,
   set_text_data__with_keys_for_tmj_object_names_that_are_not_present__will_throw_an_error)
{
   std::string maps_data_path = get_data_path() + "maps/";
   AllegroFlare::Layouts::Text layout(&get_font_bin_ref());
   layout.set_tmj_filename(maps_data_path + "layout_1-04.tmj");
   layout.initialize();

   EXPECT_THROW_WITH_MESSAGE(
      layout.set_text_data({
         { "a_key_that_does_not_exist", "SEARCHING..." },
         { "nav_bar",       "v0.14.715n" },
      }),
      std::runtime_error,
      "[AllegroFlare::Layouts::Text::set_text_data]: error: guard \"compare_maps(this->text_data, text_data)\" not met"
   );
}


TEST_F(Layouts_TextTestWithAllegroRenderingFixture,
   CAPTURE__get_layout_width__get_layout_height__will_return_the_size_of_the_layout)
{
   std::string maps_data_path = get_data_path() + "maps/";
   AllegroFlare::Layouts::Text layout(&get_font_bin_ref());
   layout.set_tmj_filename(maps_data_path + "layout_1-04.tmj");
   layout.initialize();

   layout.set_text_data({
      { "primary_label", "SEARCHING..." },
      { "nav_bar",       "v0.14.715n" },
   });

   clear();
   ALLEGRO_TRANSFORM t;
   al_identity_transform(&t);
   al_translate_transform( // TODO: Fix this
      &t,
      1920/2 - layout.get_layout_width()/2,
      1080/2 - layout.get_layout_height()/2
   );
   al_use_transform(&t);
   layout.render();

   al_flip_display();
   //sleep_for(1);
}
*/


/*
TEST_F(Layouts_TextTestWithAllegroRenderingFixture,
   CAPTURE__get_effective_width__get_effective_height__will_return_the_size_of_the_layout)
{
   std::string maps_data_path = get_data_path() + "maps/";
   AllegroFlare::Layouts::Text layout(&get_font_bin_ref());
   layout.set_tmj_filename(maps_data_path + "layout_1-04.tmj");
   layout.initialize();

   layout.set_text_data({
      { "primary_label", "SEARCHING..." },
      { "nav_bar",       "v0.14.715n" },
   });

   clear();
   ALLEGRO_TRANSFORM t;
   al_identity_transform(&t);
   al_translate_transform( // TODO: Fix this
      &t,
      1920/2 - layout.get_effective_width()/2,
      1080/2 - layout.get_effective_height()/2
   );
   al_use_transform(&t);
   layout.render();

   al_flip_display();
   //sleep_for(1);
}
*/




TEST_F(AllegroFlare_Layouts_TextTestWithAllegroRenderingFixture,
   CAPTURE__get_layout_width__get_layout_height__will_return_the_size_of_the_layout__2)
{
   ALLEGRO_COLOR orange = ALLEGRO_COLOR{1.0, 0.65, 0.0, 1.0};
   ALLEGRO_COLOR black = ALLEGRO_COLOR{0.0, 0.0, 0.0, 1.0};
   ALLEGRO_COLOR slate = ALLEGRO_COLOR{0.18, 0.31, 0.31, 1.0};
   ALLEGRO_COLOR firebrick = ALLEGRO_COLOR{0.7, 0.13, 0.13, 1.0};
   ALLEGRO_COLOR eigengrau = ALLEGRO_COLOR{0.1, 0.1, 0.12, 1.0};
   ALLEGRO_COLOR background_color = eigengrau;
   ALLEGRO_COLOR foreground_color = firebrick;

   AllegroFlare::Camera2D camera_2d;
   AllegroFlare::Shaders::FlatColor flat_color_shader;
   flat_color_shader.set_color(foreground_color);
   flat_color_shader.set_color_intensity(0.85);
   flat_color_shader.initialize();

   std::string maps_data_path = get_data_path() + "maps/";
   AllegroFlare::Layouts::Text layout(&get_font_bin_ref());
   layout.set_tmj_filename(maps_data_path + "fullscreen_layout_6-01.tmj");
   //layout.set_tmj_filename(maps_data_path + "layout_5-01.tmj");
   AllegroFlare::Generators::LoremIpsumGenerator ipsum;
   layout.set_scale(2);
   layout.initialize();

   //std::string text = "Day 184: System AI began rerouting power unexpectedly. Overload warnings ignored. "
      //"Multiple blackouts followed. Attempted manual override and AI bypassed controls. Total infrastructure "
      //"collapse imminent.";
   std::string text = "I don't know how much longer I can keep this up. The AI's been glitching for days, "
      "rerouting power all over the grid. I've tried everything - manual overrides, resets - nothing works. "
      "\n\nYesterday, half the district went dark. It's like it's thinking for itself now. I'm scared, honestly. "
      "If this keeps up, the whole city could collapse. I miss you so much.";


   layout.set_text_data({
      { "header", "LOG 1058391.324.1" },
      { "body", text },
      //{ "body", ipsum.generate_sentences(4) },
      { "version", "v12.532.r5432" },
   });

   clear();
   al_clear_to_color(background_color);
   camera_2d.setup_dimensional_projection(al_get_target_bitmap());
   ALLEGRO_TRANSFORM t;
   al_identity_transform(&t);
   al_rotate_transform_3d(&t, 0, 1, 0, 0.25);
   al_translate_transform( // TODO: Fix this
      &t,
      1920/2 - layout.get_layout_width()/2,
      1080/2 - layout.get_layout_height()/2
   );
   al_use_transform(&t);

   flat_color_shader.activate();
   layout.render();
   layout.render_debug();
   flat_color_shader.deactivate();

   al_flip_display();
   sleep_for(1);
}


TEST_F(AllegroFlare_Layouts_TextTestWithAllegroRenderingFixture,
   CAPTURE__get_layout_width__get_layout_height__will_return_the_size_of_the_layout__3)
{
   ALLEGRO_COLOR orange = ALLEGRO_COLOR{1.0, 0.65, 0.0, 1.0};
   ALLEGRO_COLOR black = ALLEGRO_COLOR{0.0, 0.0, 0.0, 1.0};
   ALLEGRO_COLOR slate = ALLEGRO_COLOR{0.18, 0.31, 0.31, 1.0};
   ALLEGRO_COLOR firebrick = ALLEGRO_COLOR{0.7, 0.13, 0.13, 1.0};
   ALLEGRO_COLOR eigengrau = ALLEGRO_COLOR{0.1, 0.1, 0.12, 1.0};
   ALLEGRO_COLOR background_color = eigengrau;
   ALLEGRO_COLOR foreground_color = firebrick;

   AllegroFlare::Camera2D camera_2d;
   AllegroFlare::Shaders::FlatColor flat_color_shader;
   flat_color_shader.set_color(foreground_color);
   flat_color_shader.set_color_intensity(0.85);
   flat_color_shader.initialize();

   std::string maps_data_path = get_data_path() + "maps/";
   AllegroFlare::Layouts::Text layout(&get_font_bin_ref());
   layout.set_tmj_filename(maps_data_path + "card_key-02.tmj");
   //layout.set_prim_mesh_atlas_filename("ascii_glyphs_12x16-08.png");
   //layout.set_tmj_filename(maps_data_path + "layout_5-01.tmj");
   AllegroFlare::Generators::LoremIpsumGenerator ipsum;
   layout.set_scale(2);
   layout.initialize();

   //std::string text = "Day 184: System AI began rerouting power unexpectedly. Overload warnings ignored. "
      //"Multiple blackouts followed. Attempted manual override and AI bypassed controls. Total infrastructure "
      //"collapse imminent.";
   std::string text = "I don't know how much longer I can keep this up. The AI's been glitching for days, "
      "rerouting power all over the grid. I've tried everything - manual overrides, resets - nothing works. "
      "\n\nYesterday, half the district went dark. It's like it's thinking for itself now. I'm scared, honestly. "
      "If this keeps up, the whole city could collapse. I miss you so much.";


   layout.set_text_data({
      { "primary_text", "CARD KEY" },
      { "data_text", "48325-7" },
      { "version_text", "182.518x : 91.1-5n" },
      //{ "body", ipsum.generate_sentences(4) },
      //{ "version", "v12.532.r5432" },
   });

   clear();
   al_clear_to_color(background_color);
   camera_2d.setup_dimensional_projection(al_get_target_bitmap());
   ALLEGRO_TRANSFORM t;
   al_identity_transform(&t);
   al_rotate_transform_3d(&t, 0, 1, 0, 0.25);
   al_translate_transform( // TODO: Fix this
      &t,
      1920/2 - layout.get_layout_width()/2,
      1080/2 - layout.get_layout_height()/2
   );
   al_use_transform(&t);

   flat_color_shader.activate();
   layout.render();
   flat_color_shader.deactivate();

   al_flip_display();
   sleep_for(1);
}


TEST_F(AllegroFlare_Layouts_TextTestWithViewer, CAPTURE__will_correctly_align_the_text)
{
   std::string text = "Day 184: System AI began rerouting power unexpectedly. Overload warnings ignored. "
      "Multiple blackouts followed. Attempted manual override and AI bypassed controls. Total infrastructure "
      "collapse imminent.";
   setup_subject(
      "text_alignment_test-01.tmj",
      "ascii_glyphs_12x16-08-4x_r.png",
      {
         { "text_a", "Some Text Here" },
         { "text_b", "Text to the right" },
         { "text_c", "Some Text Here" },
         { "text_d", "CUSTOM FONT" },
         { "center_center", text },
         { "right_bottom", text },
      },
      3
   );
   view_subject();
   sleep_for(1);
}


