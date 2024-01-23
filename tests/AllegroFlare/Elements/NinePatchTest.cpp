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


TEST_F(AllegroFlare_Elements_NinePatchTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::NinePatch nine_patch;
   std::string expected_error_message =
      "NinePatch::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(nine_patch.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_NinePatchTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::NinePatch nine_patch;
   std::string expected_error_message =
      "NinePatch::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(nine_patch.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_NinePatchTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   ALLEGRO_BITMAP *source_texture = get_bitmap_bin_ref().auto_get("9SliceSprites-0.png");
   ASSERT_NE(nullptr, source_texture);

   AllegroFlare::Elements::NinePatch nine_patch;
   nine_patch.build_mesh();
   nine_patch.set_source_texture(source_texture);
   nine_patch.render();

   al_flip_display();
   sleep_for(1);
}


