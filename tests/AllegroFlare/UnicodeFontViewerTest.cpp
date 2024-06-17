
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


#include <AllegroFlare/UnicodeFontViewer.hpp>
#include <allegro5/allegro_primitives.h>


class AllegroFlare_UnicodeFontViewerTest : public ::testing::Test
{};

class AllegroFlare_UnicodeFontViewerTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/UnicodeFontViewer.hpp>


TEST_F(AllegroFlare_UnicodeFontViewerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::UnicodeFontViewer unicode_font_viewer;
}


TEST_F(AllegroFlare_UnicodeFontViewerTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::UnicodeFontViewer unicode_font_viewer;
   EXPECT_THROW_GUARD_ERROR(
      unicode_font_viewer.render(),
      "AllegroFlare::UnicodeFontViewer::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_UnicodeFontViewerTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::UnicodeFontViewer unicode_font_viewer;
   EXPECT_THROW_GUARD_ERROR(
      unicode_font_viewer.render(),
      "AllegroFlare::UnicodeFontViewer::render",
      "al_is_font_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_UnicodeFontViewerTest, render__without_ttf_addon_initialized__raises_an_error)
{
   al_init();
   al_init_font_addon();
   AllegroFlare::UnicodeFontViewer unicode_font_viewer;
   EXPECT_THROW_GUARD_ERROR(
      unicode_font_viewer.render(),
      "AllegroFlare::UnicodeFontViewer::render",
      "al_is_ttf_addon_initialized()"
   );
   al_shutdown_font_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_UnicodeFontViewerTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();
   AllegroFlare::UnicodeFontViewer unicode_font_viewer;
   EXPECT_THROW_GUARD_ERROR(
      unicode_font_viewer.render(),
      "AllegroFlare::UnicodeFontViewer::render",
      "al_is_primitives_addon_initialized()"
   );
   al_shutdown_ttf_addon();
   al_shutdown_font_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_UnicodeFontViewerTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_primitives_addon();
   AllegroFlare::UnicodeFontViewer unicode_font_viewer;
   EXPECT_THROW_GUARD_ERROR(
      unicode_font_viewer.render(),
      "AllegroFlare::UnicodeFontViewer::render",
      "font_bin"
   );
   al_shutdown_primitives_addon();
   al_shutdown_ttf_addon();
   al_shutdown_font_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_UnicodeFontViewerTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::UnicodeFontViewer unicode_font_viewer(&font_bin, "Bravura.otf", 0x1D100);

   al_clear_to_color(ALLEGRO_COLOR{0.04, 0.05, 0.08, 1});

   unicode_font_viewer.render();

   al_flip_display();
   //sleep_for(3);
}


