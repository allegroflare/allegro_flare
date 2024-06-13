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
   EXPECT_THROW_GUARD_ERROR(
      nine_patch.initialize(),
      "AllegroFlare::Elements::NinePatch::initialize",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Elements_NinePatchTest, initialize__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::NinePatch nine_patch;
   EXPECT_THROW_GUARD_ERROR(
      nine_patch.initialize(),
      "AllegroFlare::Elements::NinePatch::initialize",
      "al_is_primitives_addon_initialized()"
   );
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

   // Set the inner size of this patch
   nine_patch.set_center_column_width(256);
   nine_patch.set_middle_row_height(128);

   // Set an initial texture
   nine_patch.set_source_texture(source_texture);

   // Initialize the patch
   nine_patch.initialize();

   // Build a placement for our patch
   AllegroFlare::Placement2D place;
   place.size.x = 256 + 48*2;
   place.size.y = 128 + 48*2;
   place.position.x = 1920 / 2;
   place.position.y = 1080 / 2;

   { // Render
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});

      // Rende our patch
      place.start_transform();
      nine_patch.render();
      place.restore_transform();

      al_flip_display();
      sleep_for(1);
   }
}


