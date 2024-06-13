
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/ChoiceRenderer.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


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
   EXPECT_THROW_GUARD_ERROR(
      choice_renderer.render(),
      "AllegroFlare::Elements::DialogBoxRenderers::ChoiceRenderer::render",
      "choice_dialog_box"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChoiceRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__renders_the_elements)
{
   std::string choice_box_prompt = "Are you making progress?";
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "Absolutely!", "GOTO A" },
     { "I would seem that I am", "GOTO B" },
     { "I think so?", "GOTO C" },
   };
   AllegroFlare::Elements::DialogBoxes::Choice choice_dialog_box(choice_box_prompt, choice_options);
   choice_dialog_box.initialize();

   choice_dialog_box.move_cursor_position_down();

   AllegroFlare::Elements::DialogBoxRenderers::ChoiceRenderer choice_renderer(
      &get_font_bin_ref(),
      &get_bitmap_bin_ref(),
      &choice_dialog_box
   );

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, choice_renderer.get_width(), choice_renderer.get_height() };

   clear();
   place.start_transform();
   choice_renderer.render();
   place.restore_transform();
   al_flip_display();

   SUCCEED();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChoiceRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__renders_elements_in_motion_when_revealing)
{
   //std::string choice_box_prompt = "Do you have any information about the whereabouts of the missing villagers?";
   std::string choice_box_prompt = "Do you know anything regarding the whereabouts and well-being of the villagers "
                                   "who mysteriously disappeared without a trace, leaving their loved ones in anguish "
                                   "and uncertainty?";
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "I saw some strange tracks leading deeper into the forest. They might be related.", "GOTO A" },
     { "I haven't seen anyone, but I heard eerie whispers in the dark last night.", "GOTO B" },
     { "I'm not from around here, so I don't have any information on the villagers.", "GOTO C" },
   };
   //std::string choice_box_prompt = "Are you making progress?";
   //std::vector<std::pair<std::string, std::string>> choice_options = {
     //{ "Absolutely!", "GOTO A" },
     //{ "I would seem that I am", "GOTO B" },
     //{ "I think so?", "GOTO C" },
   //};
   AllegroFlare::Elements::DialogBoxes::Choice choice_dialog_box(choice_box_prompt, choice_options);
   choice_dialog_box.initialize();

   choice_dialog_box.move_cursor_position_down();

   int passes = 120 * 5;
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


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChoiceRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__with_a_selection_cursor_box_injected__will_render_it)
{
   //std::string choice_box_prompt = "Do you have any information about the whereabouts of the missing villagers?";
   //std::string choice_box_prompt = "Do you know anything regarding the whereabouts and well-being of the villagers "
                                   //"who mysteriously disappeared without a trace, leaving their loved ones in anguish "
                                   //"and uncertainty?";
   //std::vector<std::pair<std::string, std::string>> choice_options = {
     //{ "I saw some strange tracks leading deeper into the forest. They might be related.", "GOTO A" },
     //{ "I haven't seen anyone, but I heard eerie whispers in the dark last night.", "GOTO B" },
     //{ "I'm not from around here, so I don't have any information on the villagers.", "GOTO C" },
   //};
   std::string choice_box_prompt = "Are you making progress?";
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "Absolutely!", "GOTO A" },
     { "I would seem that I am", "GOTO B" },
     { "I think so?", "GOTO C" },
   };
   AllegroFlare::Elements::DialogBoxes::Choice choice_dialog_box(choice_box_prompt, choice_options);
   choice_dialog_box.initialize();

   AllegroFlare::Elements::SelectionCursorBox my_selection_cursor_box;

   //choice_dialog_box.advance(); // Advance text so end so that selection box is visible and cursor can be moved
   //choice_dialog_box.move_cursor_position_down();


   // Set the initial position for our cursor

   AllegroFlare::Elements::DialogBoxRenderers::ChoiceRenderer choice_renderer_for_dimensions(
      &get_font_bin_ref(),
      &get_bitmap_bin_ref(),
      &choice_dialog_box
   );

   std::tuple<float, float, float, float> selection_dimensions =
         choice_renderer_for_dimensions.calculate_dimensions_of_current_selection();
   choice_renderer_for_dimensions.helper__set_selection_cursor_box_dimensions_to(
         &my_selection_cursor_box,
         selection_dimensions
      );



   int passes = 120 * 5;
   int cursor_presses = 4;
   for (int i=0; i<passes; i++)
   {
      bool move_cursor_in_this_pass = false;
      if (i % (passes / cursor_presses) == (passes / cursor_presses) / 2) move_cursor_in_this_pass = true;

      if (move_cursor_in_this_pass)
      {
         // Move the cursor down
         choice_dialog_box.move_cursor_position_down();

         // Update the cursor position
         AllegroFlare::Elements::DialogBoxRenderers::ChoiceRenderer choice_renderer_for_dimensions(
            &get_font_bin_ref(),
            &get_bitmap_bin_ref(),
            &choice_dialog_box
         );

         std::tuple<float, float, float, float> selection_dimensions =
               choice_renderer_for_dimensions.calculate_dimensions_of_current_selection();
         choice_renderer_for_dimensions.helper__reposition_selection_cursor_box_dimensions_to(
               &my_selection_cursor_box,
               selection_dimensions
            );
      }

      // Update
      my_selection_cursor_box.update();
      choice_dialog_box.update();

      // Render
      AllegroFlare::Elements::DialogBoxRenderers::ChoiceRenderer choice_renderer(
         &get_font_bin_ref(),
         &get_bitmap_bin_ref(),
         &choice_dialog_box
      );
      choice_renderer.set_selection_cursor_box(&my_selection_cursor_box);
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


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChoiceRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__when_speaking_character_is_present__renders_the_speaking_character_name_tag)
{
   //std::string choice_box_prompt = "Do you have any information about the whereabouts of the missing villagers?";
   std::string choice_box_prompt = "Do you know anything regarding the whereabouts and well-being of the villagers "
                                   "who mysteriously disappeared without a trace, leaving their loved ones in anguish "
                                   "and uncertainty?";
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "I saw some strange tracks leading deeper into the forest. They might be related.", "GOTO A" },
     { "I haven't seen anyone, but I heard eerie whispers in the dark last night.", "GOTO B" },
     { "I'm not from around here, so I don't have any information on the villagers.", "GOTO C" },
   };
   //std::string choice_box_prompt = "Are you making progress?";
   //std::vector<std::pair<std::string, std::string>> choice_options = {
     //{ "Absolutely!", "GOTO A" },
     //{ "I would seem that I am", "GOTO B" },
     //{ "I think so?", "GOTO C" },
   //};
   AllegroFlare::Elements::DialogBoxes::Choice choice_dialog_box(choice_box_prompt, choice_options);
   choice_dialog_box.initialize();

   choice_dialog_box.move_cursor_position_down();

   int passes = 120 * 5;
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
      choice_renderer.set_speaking_character_name("Princess");
      choice_renderer.set_showing_speaking_character_name(true);
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


