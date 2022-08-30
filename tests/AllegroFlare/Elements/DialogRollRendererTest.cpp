
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_DialogRollRendererTest : public ::testing::Test
{};

class AllegroFlare_Elements_DialogRollRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/DialogRollRenderer.hpp>


TEST_F(AllegroFlare_Elements_DialogRollRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogRollRenderer dialog_roll_renderer;
}


TEST_F(AllegroFlare_Elements_DialogRollRendererTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::DialogRollRenderer dialog_roll_renderer;
   std::string expected_error_message =
      "DialogRollRenderer::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_roll_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_DialogRollRendererTestWithAllegroRenderingFixture,
   DISABLED__render__without_a_font_bin__will_throw_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_DialogRollRendererTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::DialogRollRenderer dialog_roll_renderer(&get_font_bin_ref());
   dialog_roll_renderer.render();
}


TEST_F(AllegroFlare_Elements_DialogRollRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_as_expected)
{
   AllegroFlare::Elements::DialogRollRenderer dialog_roll_renderer(&get_font_bin_ref(), {
      { "Alice", "This is some dialog." },
      { "Bob",   "This is some dialog, too." },
      { "",      "I feel like I've heard this one before. Not to mention there's probably "
                 "going to be a multiline version." },
   });

   clear();
   dialog_roll_renderer.render();
   al_flip_display();

   sleep(1);
}


