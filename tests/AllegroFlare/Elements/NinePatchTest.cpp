#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Elements/NinePatch.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_Elements_NinePatchTest : public ::testing::Test {};
class AllegroFlare_Elements_NinePatchTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_Elements_NinePatchTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::NinePatch nine_patch;
}


TEST_F(AllegroFlare_Elements_NinePatchTest, initialize__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::NinePatch nine_patch;
   std::string expected_error_message =
      "NinePatch::initialize: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(nine_patch.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_NinePatchTest, initialize__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::NinePatch nine_patch;
   std::string expected_error_message =
      "NinePatch::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(nine_patch.initialize(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_NinePatchTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   ALLEGRO_BITMAP *source_texture = get_bitmap_bin_ref().auto_get("9SliceSprites-0.png");
   ASSERT_NE(nullptr, source_texture);

   AllegroFlare::Elements::NinePatch nine_patch;
   nine_patch.set_source_texture(source_texture);
   nine_patch.initialize();

   nine_patch.render();

   al_flip_display();
   //sleep_for(1);
}


TEST_F(AllegroFlare_Elements_NinePatchTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_as_expected)
{
   ALLEGRO_BITMAP *source_texture = get_bitmap_bin_ref().auto_get("panel-transparent-center-010.png");
   ASSERT_NE(nullptr, source_texture);

   AllegroFlare::Elements::NinePatch nine_patch;

   // Build the UVs
   nine_patch.set_a_uv({ 0, 0, 32, 32 });
   nine_patch.set_b_uv({ 32, 0, 64, 32 });
   nine_patch.set_c_uv({ 64, 0, 96, 32 });
   nine_patch.set_d_uv({ 0, 32, 32, 64 });
   nine_patch.set_e_uv({ 32, 32, 64, 64 });
   nine_patch.set_f_uv({ 64, 32, 96, 64 });
   nine_patch.set_g_uv({ 0, 64, 32, 96 });
   nine_patch.set_h_uv({ 32, 64, 64, 96 });
   nine_patch.set_i_uv({ 64, 64, 96, 96 });

   // Set the dimensions
   nine_patch.set_left_column_width(48);
   nine_patch.set_right_column_width(48);
   nine_patch.set_top_row_height(48);
   nine_patch.set_bottom_row_height(48);

   nine_patch.set_source_texture(source_texture);
   nine_patch.initialize();

   nine_patch.render();

   al_flip_display();
   sleep_for(1);
}


