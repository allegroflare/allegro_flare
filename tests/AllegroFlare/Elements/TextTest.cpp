
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Color.hpp>


class AllegroFlare_Elements_TextTest : public ::testing::Test
{};

class AllegroFlare_Elements_TextTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/Text.hpp>


TEST_F(AllegroFlare_Elements_TextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Text text;
}


TEST_F(AllegroFlare_Elements_TextTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::Text text;
   EXPECT_THROW_GUARD_ERROR(
      text.render(),
      "AllegroFlare::Elements::Text::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Elements_TextTestWithAllegroRenderingFixture,
   render__without_a_font_bin__will_throw_an_error)
{
   AllegroFlare::Elements::Text text;
   EXPECT_THROW_GUARD_ERROR(
      text.render(),
      "AllegroFlare::Elements::Text::obtain_font",
      "font_bin"
   );
}


TEST_F(AllegroFlare_Elements_TextTestWithAllegroRenderingFixture,
   CAPTURE__render__will_draw_the_text_to_the_screen)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::Elements::Text text(&font_bin);
   text.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_TextTestWithAllegroRenderingFixture,
   fit_placement_width_and_height_to_text__will_set_the_placement_width_and_height_to_the_dimensions_of_the_text)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::Elements::Text text(&font_bin);
   text.fit_placement_width_and_height_to_text();

   EXPECT_EQ(192, text.get_placement().size.x);
   EXPECT_EQ(48, text.get_placement().size.y);
}


TEST_F(AllegroFlare_Elements_TextTestWithAllegroRenderingFixture,
   CAPTURE__render__with_customizations_on_color_font_identifier_and_font_size__will_render_as_expected)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::Elements::Text text(&font_bin);
   text.fit_placement_width_and_height_to_text();
   text.set_text("This is Custom Text");
   text.set_font_identifier("plantin-mt-light.ttf");
   text.set_font_size(-120);
   text.set_color(AllegroFlare::Color::Aquamarine);
   text.get_placement_ref().position.x = 1920/2;
   text.get_placement_ref().position.y = 1080/2;

   text.render();

   al_flip_display();
}

