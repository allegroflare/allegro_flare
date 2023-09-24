
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <AllegroFlare/Elements/DialogBoxRenderers/ChoiceRenderer.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#ifdef _WIN32
#define TEST_FIXTURE_FONT_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/fonts/"
#else
#define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/fonts/"
#endif


class AllegroFlare_Elements_DialogBoxRenderers_ChoiceRendererTest : public ::testing::Test {};
class AllegroFlare_Elements_DialogBoxRenderers_ChoiceRendererWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChoiceRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::ChoiceRenderer choice_renderer;
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChoiceRendererTest,
   render__without_a_choice_dialog_box__throws_an_exception)
{
   al_init();
   AllegroFlare::Elements::DialogBoxRenderers::ChoiceRenderer choice_renderer;
   std::string expected_error_message = "ChoiceRenderer::render: error: guard \"choice_dialog_box\" not met";
   ASSERT_THROW_WITH_MESSAGE(choice_renderer.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChoiceRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__renders_the_elements)
{
   get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER);

   std::string choice_box_prompt = "Are you making progress?";
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "Absolutely!", "GOTO A" },
     { "I would seem that I am", "GOTO B" },
     { "I think so?", "GOTO C" },
   };
   AllegroFlare::Elements::DialogBoxes::Choice choice_dialog_box(choice_box_prompt, choice_options);
   choice_dialog_box.initialize();

   choice_dialog_box.move_cursor_position_down();

   int passes = 120;
   for (int i=0; i<passes; i++)
   {
      // Update
      choice_dialog_box.update();

      // Render
      AllegroFlare::Elements::DialogBoxRenderers::ChoiceRenderer choice_renderer(
         &get_font_bin_ref(),
         &get_bitmap_bin_ref(),
         &choice_dialog_box
      );
      choice_renderer.set_age(choice_dialog_box.infer_age());

      AllegroFlare::Placement2D place{ 1920/2, 1080/2, choice_renderer.get_width(), choice_renderer.get_height() };

      clear();
      place.start_transform();
      choice_renderer.render();
      place.restore_transform();
      al_flip_display();
   }

   SUCCEED();
}


