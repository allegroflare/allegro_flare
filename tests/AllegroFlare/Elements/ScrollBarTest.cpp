
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_ScrollBarTest : public ::testing::Test
{};

class AllegroFlare_Elements_ScrollBarTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/ScrollBar.hpp>


TEST_F(AllegroFlare_Elements_ScrollBarTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::ScrollBar scroll_bar;
}


TEST_F(AllegroFlare_Elements_ScrollBarTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::ScrollBar scroll_bar;
   std::string expected_error_message =
      "ScrollBar::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(scroll_bar.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_ScrollBarTest, render__without_the_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::ScrollBar scroll_bar;
   std::string expected_error_message =
      "ScrollBar::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(scroll_bar.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_ScrollBarTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::ScrollBar scroll_bar;
   scroll_bar.render();
}


TEST_F(AllegroFlare_Elements_ScrollBarTestWithAllegroRenderingFixture,
   CAPTURE__render__will_draw_the_bar_as_expected)
{
   AllegroFlare::Placement2D place = build_centered_placement(10, 300);
   AllegroFlare::Elements::ScrollBar scroll_bar;

   place.start_transform();
   scroll_bar.render();
   al_flip_display();
   place.restore_transform();
}


TEST_F(AllegroFlare_Elements_ScrollBarTestWithAllegroRenderingFixture,
   CAPTURE__various_examples_will_render_as_expected)
{
   AllegroFlare::Placement2D place = build_centered_placement(10, 300);

   place.start_transform();

   AllegroFlare::Elements::ScrollBar(-300, 0, 200, 0.0).render();
   AllegroFlare::Elements::ScrollBar(0, 0, 300, 1.0 - 0.618033).render();
   AllegroFlare::Elements::ScrollBar(300, 0, 180, 1.0).render();

   draw_crosshair(-300, 0);
   draw_crosshair(0, 0);
   draw_crosshair(0, 300, ALLEGRO_COLOR{0, 1, 0, 1});
   draw_crosshair(300, 180, ALLEGRO_COLOR{0, 1, 0, 1});

   al_flip_display();
   place.restore_transform();
}


