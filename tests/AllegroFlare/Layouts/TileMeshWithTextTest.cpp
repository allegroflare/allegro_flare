#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Layouts/TileMeshWithText.hpp>
//#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <AllegroFlare/Generators/LoremIpsumGenerator.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Shaders/FlatColor.hpp>


class AllegroFlare_Layouts_TileMeshWithTextTest : public ::testing::Test {};
class AllegroFlare_Layouts_TileMeshWithTextTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Layouts_TileMeshWithTextTestWithViewer
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
   AllegroFlare::Layouts::TileMeshWithText layout;

   void SetUp()
   {
      AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();

      flat_color_shader.set_color(foreground_color);
      flat_color_shader.set_color_intensity(0.85);
      flat_color_shader.initialize();

      layout.set_bitmap_bin(&get_bitmap_bin_ref());
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
         layout.set_prim_mesh_atlas_filename(atlas_filename);
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
         1920/2 - layout.get_effective_width()/2,
         1080/2 - layout.get_effective_height()/2
      );
      al_use_transform(&t);

      //flat_color_shader.activate();
      layout.render();
      //flat_color_shader.deactivate();

      al_flip_display();
   }
};


TEST_F(AllegroFlare_Layouts_TileMeshWithTextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Layouts::TileMeshWithText layout;
}


TEST_F(AllegroFlare_Layouts_TileMeshWithTextTest, initialize__without_a_bitmap_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::Layouts::TileMeshWithText layout;
   std::string expected_error_message =
      "[AllegroFlare::Layouts::TileMeshWithText::initialize]: error: guard \"bitmap_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(layout.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


/*

TEST_F(AllegroFlare_Layouts_TileMeshWithTextTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   std::string maps_data_path = get_data_path() + "maps/";
   AllegroFlare::Layouts::TileMeshWithText layout(&get_bitmap_bin_ref(), &get_font_bin_ref());
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


TEST_F(AllegroFlare_Layouts_TileMeshWithTextTestWithAllegroRenderingFixture,
   set_text_data__with_keys_for_tmj_object_names_that_are_not_present__will_throw_an_error)
{
   std::string maps_data_path = get_data_path() + "maps/";
   AllegroFlare::Layouts::TileMeshWithText layout(&get_bitmap_bin_ref(), &get_font_bin_ref());
   layout.set_tmj_filename(maps_data_path + "layout_1-04.tmj");
   layout.initialize();

   EXPECT_THROW_WITH_MESSAGE(
      layout.set_text_data({
         { "a_key_that_does_not_exist", "SEARCHING..." },
         { "nav_bar",       "v0.14.715n" },
      }),
      std::runtime_error,
      "[AllegroFlare::Layouts::TileMeshWithText::set_text_data]: error: guard \"compare_maps(this->text_data, text_data)\" not met"
   );
}


TEST_F(AllegroFlare_Layouts_TileMeshWithTextTestWithAllegroRenderingFixture,
   CAPTURE__get_effective_width__get_effective_height__will_return_the_size_of_the_layout)
{
   std::string maps_data_path = get_data_path() + "maps/";
   AllegroFlare::Layouts::TileMeshWithText layout(&get_bitmap_bin_ref(), &get_font_bin_ref());
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


TEST_F(AllegroFlare_Layouts_TileMeshWithTextTestWithAllegroRenderingFixture,
   CAPTURE__get_effective_width__get_effective_height__will_return_the_size_of_the_layout__2)
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
   AllegroFlare::Layouts::TileMeshWithText layout(&get_bitmap_bin_ref(), &get_font_bin_ref());
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
      1920/2 - layout.get_effective_width()/2,
      1080/2 - layout.get_effective_height()/2
   );
   al_use_transform(&t);

   flat_color_shader.activate();
   layout.render();
   flat_color_shader.deactivate();

   al_flip_display();
   sleep_for(1);
}


TEST_F(AllegroFlare_Layouts_TileMeshWithTextTestWithAllegroRenderingFixture,
   CAPTURE__get_effective_width__get_effective_height__will_return_the_size_of_the_layout__3)
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
   AllegroFlare::Layouts::TileMeshWithText layout(&get_bitmap_bin_ref(), &get_font_bin_ref());
   layout.set_tmj_filename(maps_data_path + "card_key-02.tmj");
   layout.set_prim_mesh_atlas_filename("ascii_glyphs_12x16-08.png");
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
      1920/2 - layout.get_effective_width()/2,
      1080/2 - layout.get_effective_height()/2
   );
   al_use_transform(&t);

   flat_color_shader.activate();
   layout.render();
   flat_color_shader.deactivate();

   al_flip_display();
   sleep_for(1);
}


TEST_F(AllegroFlare_Layouts_TileMeshWithTextTestWithViewer, CAPTURE__will_correctly_align_the_text)
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


TEST_F(AllegroFlare_Layouts_TileMeshWithTextTestWithViewer, CAPTURE__with_tiles_that_are_flipped__will_render_as_expected__1)
{
   setup_subject(
      "reticle_example_3-01.tmj",
      "ascii_glyphs_12x16-09.png-result.png",
      {
         { "cardinal", "SSW" },
         { "box1", "TIER" },
         { "box2", "HEX" },
         { "box3", "APOGEE" },
         { "speed", "266 KPH" },
      }
   );
   view_subject();
   sleep_for(1);
}


TEST_F(AllegroFlare_Layouts_TileMeshWithTextTestWithViewer, CAPTURE__with_tiles_that_are_flipped__will_render_as_expected__2)
{
   setup_subject(
      "reticle_with_flipped_tiles_1-01.tmj",
      "ascii_glyphs_12x16-08.png",
      {}
   );
   view_subject();
   sleep_for(1);
}


TEST_F(AllegroFlare_Layouts_TileMeshWithTextTestWithViewer, CAPTURE__with_tiles_that_are_flipped__will_render_as_expected__3)
{
   setup_subject(
      "as_ui-01.tmj",
      "ascii_glyphs_12x16-09.png-result.png",
      {
         { "label1", "asdf" },
         { "body1", "asdf" },
         { "stat1", "asdf" },

         { "label2", "asdf" },
         { "body2", "asdf" },
      }
   );
   view_subject();
   sleep_for(1);
}


TEST_F(AllegroFlare_Layouts_TileMeshWithTextTestWithViewer, CAPTURE__with_tiles_that_are_flipped__will_render_as_expected__4)
{
   setup_subject(
      "tables_layout-01.tmj",
      "ascii_glyphs_12x16-09.png-result.png",
      {
         { "supertext1", "CLUB-CATT-CORPORATION" },
         { "text1", "UA 571-C" },
         { "text2", "REMOTE SENTRY WEAPON SYSTEM" },
         { "text3", "TEST\nENGAGED\nINTERROGATE" },
         { "text4", "AUTO\nSELECTIVE" },
         { "text5", "TARGET PROFILE" },
            { "list5", "SOFT\nSEMIHARD\nHARD" },
         { "text6", "SPECTRAL PROFILE" },
            { "list6", "BIO\nINERT" },
         { "text7", "TARGET SELECT" },
            { "list7", "MULTI SPEC\nINFRA RED\nUV" },
         { "text8", "SYSTEM MODE" },
            { "list8", "AUTO-REMOTE\nMAN-OVERRIDE\nSEMI-AUTO" },
         { "text9", "WEAPON" },
            { "list9", "SAFE\nARMED" },
         { "text10", "IFF STATUS" },
            //{ "list9", "SAFE\nARMED" },
         { "text11", "TEST ROUTINE" },
         { "subtext1", "UNITED STATES CORPS OF MINERS" },
      }
   );
   view_subject();
   sleep_for(1);
}


TEST_F(AllegroFlare_Layouts_TileMeshWithTextTestWithViewer, CAPTURE__with_tiles_that_are_flipped__will_render_as_expected__5)
{
   setup_subject(
     "layout_with_opacity-01.tmj",
      "ascii_glyphs_12x16-10-1000x.png-result.png",
      {
      }
   );
   view_subject();
   sleep_for(1);
}


TEST_F(AllegroFlare_Layouts_TileMeshWithTextTestWithViewer, CAPTURE__with_tiles_that_are_flipped__will_render_as_expected__6)
{
   setup_subject(
      "circuit-01.tmj",
      "ascii_glyphs_12x16-11-1000x.png-result.png",
      {
         { "element_num", "123" },
         { "product_subversion", "123" },
         { "cpu_num", "123" },
         { "product", "123" },
         { "channel_numbers", "123" },
         { "processor_spec", "123" },
         { "small_number", "123" },
         { "product_spec_text", "123" },
         { "company", "123" },
         { "product_num", "123" },
         { "serial", "82789BO-97BA-QQ9N9-ADGA07B" },
      }
   );
   view_subject();
   sleep_for(1);
}


TEST_F(AllegroFlare_Layouts_TileMeshWithTextTestWithViewer, CAPTURE__with_tiles_that_are_flipped__will_render_as_expected__7)
{
   setup_subject(
      "8_box_layout-02.tmj",
      "ascii_glyphs_12x16-11-1000x.png-result.png",
      {
         { "screen_title_text", "ARMORY" },

         { "item1_title",        "ENFORCER" },
         { "item1_ammo_counter", "9 / 19" },
         //{ "slot1_number",       "1" },

         { "item2_title",        "HYPERCLAW" },
         { "item2_ammo_counter", "128 / 255" },
         //{ "slot2_number",       "1" },

         { "item3_title",        "ECLIPSE X-7" },
         { "item3_ammo_counter", "13 / 17" },
         //{ "slot2_number",       "1" },

         { "item4_title",        "NEUROBLADE 92" },
         { "item4_ammo_counter", "8 / 8" },
         //{ "slot2_number",       "1" },

         { "item5_title",        "ZENITH 7" },
         { "item5_ammo_counter", "26 / 28" },
         //{ "slot2_number",       "1" },

         { "item6_title",        "SHREDDER" },
         { "item6_ammo_counter", "321 / 321" },
         //{ "slot2_number",       "1" },

         { "item7_title",        "SHADOWSPARK" },
         { "item7_ammo_counter", "32 / 32" },
         //{ "slot2_number",       "1" },

         { "item8_title",        "DOOM BLADE" },
         { "item8_ammo_counter", "52 / 52" },
         //{ "slot2_number",       "1" },
      },
      1
   );
   view_subject();
   sleep_for(1);
}


