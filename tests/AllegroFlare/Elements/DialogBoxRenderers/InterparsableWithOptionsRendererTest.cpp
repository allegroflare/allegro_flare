
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxRenderers/InterparsableWithOptionsRenderer.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <allegro5/allegro_primitives.h>
#include <chrono>
#include <thread>

class AllegroFlare_Elements_DialogBoxRenderers_InterparsableWithOptionsRendererTest : public ::testing::Test {};
class AllegroFlare_Elements_DialogBoxRenderers_InterparsableWithOptionsRendererWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions build_dialog_box(
      std::string speaking_character = "Bob",
      std::vector<std::string> pages = { "Hello to you!" },
      std::vector<std::pair<std::string, std::string>> options = {
         { "Hi!", "GOTO A" },
         { "Go away!", "GOTO B" },
      }
   )
   {
      AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions result;
      result.set_speaking_character(speaking_character);
      result.set_pages(pages);
      result.set_options(options);
      result.initialize(); // TODO: Check if required right?
      return result;
   }
};


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableWithOptionsRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer you_got_an_item_renderer;
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableWithOptionsRendererWithAllegroRenderingFixtureTest,
   render__without_a_choice_dialog_box__throws_an_exception)
{
   AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer renderer;
   renderer.set_font_bin(&get_font_bin_ref());
   EXPECT_THROW_GUARD_ERROR(
      renderer.render(),
      "AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer::render",
      "choice_dialog_box"
   );
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableWithOptionsRendererWithAllegroRenderingFixtureTest,
   FOCUS__CAPTURE__render__when_the_dialog_box_is_finished__renders_special_empty_text)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions dialog_box = build_dialog_box();
   AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer dialog_box_renderer(&font_bin);
   dialog_box_renderer.set_choice_dialog_box(&dialog_box);
   //dialog_box_renderer.set_current_page_text_with_formatting("This dialog is finished");
   dialog_box_renderer.set_is_finished(true);
   
   AllegroFlare::Placement2D place{ 1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height() };

   clear();

   place.start_transform();
   dialog_box_renderer.render();
   place.restore_transform();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableWithOptionsRendererWithAllegroRenderingFixtureTest,
   FOCUS__CAPTURE__render__draws_multiline_dialog)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions dialog_box = build_dialog_box(
      "Petunia",
      {
         "This is some dialog test text. In this case, there's a (em)lot(/em) of text that will need to fit on "
            "multiple lines."
      }
   );

   //std::string page_text =
      //"This is some dialog test text. In this case, there's a lot of text that will need to fit on multiple lines.";
   AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer dialog_box_renderer(&font_bin);
   dialog_box_renderer.set_choice_dialog_box(&dialog_box);
   //dialog_box_renderer.set_current_page_text_with_formatting(page_text);

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height() };

   clear();

   place.start_transform();
   dialog_box_renderer.render();
   place.restore_transform();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableWithOptionsRendererWithAllegroRenderingFixtureTest,
   FOCUS__CAPTURE__render__on_a_text_page_that_has_formatting_and_operational_tags_in_it__will_not_display_tags)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions dialog_box = build_dialog_box();

   std::string page_text =
      "This is dialog text that has (italic)some(/italic) formatting inside the source text. However, the "
      "formatting codes (bold)will(/bold) be removed when rendered.";
   AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer dialog_box_renderer(&font_bin);
   dialog_box_renderer.set_choice_dialog_box(&dialog_box);
   dialog_box_renderer.set_current_page_text_with_formatting(page_text);

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height() };

   clear();

   place.start_transform();
   dialog_box_renderer.render();
   place.restore_transform();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableWithOptionsRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__will_show_a_reveal_animation_respecting_age)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions dialog_box = build_dialog_box();

   std::string page_text =
      "This is some dialog test text. In this case, there's a lot of text that will need to fit on multiple lines.";
   AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer dialog_box_renderer(&font_bin);
   dialog_box_renderer.set_choice_dialog_box(&dialog_box);
   dialog_box_renderer.set_current_page_text_with_formatting(page_text);

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height() };

   float started_at = al_get_time();
   for (int passes=0; passes<30; passes++)
   {
      float age = al_get_time() - started_at;
      dialog_box_renderer.set_age(age);

      clear();

      place.start_transform();
      dialog_box_renderer.render();
      place.restore_transform();
      al_flip_display();

      sleep_for_frame();
   }
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableWithOptionsRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__will_propertly_render_num_revealed_characters)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions dialog_box = build_dialog_box();

   std::string page_text = "Some test dialog text that will reveal characters sequentially when rendering.";

   int num_revealed_characters = 0;
   for (unsigned i=0; i<page_text.size(); i++)
   {
      num_revealed_characters++;

      AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer dialog_box_renderer(&font_bin);
      dialog_box_renderer.set_choice_dialog_box(&dialog_box);
      dialog_box_renderer.set_current_page_text_with_formatting(page_text);
      dialog_box_renderer.set_num_revealed_characters(num_revealed_characters);
      if (num_revealed_characters >= page_text.size()) dialog_box_renderer.set_page_is_finished(true);

      AllegroFlare::Placement2D place{
         1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height()
      };

      clear();

      place.start_transform();
      dialog_box_renderer.render();
      place.restore_transform();

      //al_flip_display();
      //std::this_thread::sleep_for(std::chrono::microseconds(10000)); // add sleep for more obvious visual delay
   }
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableWithOptionsRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__with_text_formatting_tags_using_the_default_syntax__will_render_the_formatted_text)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions dialog_box = build_dialog_box();

   std::string page_text = "Some test (em)dialog text(/em) that will reveal characters sequentially when rendering.";

   int num_revealed_characters = 0;
   float time_start = al_get_time();
   for (unsigned i=0; i<page_text.size(); i++)
   {
      num_revealed_characters++;

      float age = al_get_time() - time_start;
      
      AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer dialog_box_renderer(&font_bin);
      dialog_box_renderer.set_speaking_character_name("Princess");
      dialog_box_renderer.set_showing_speaking_character_name(true);
      dialog_box_renderer.set_choice_dialog_box(&dialog_box);
      dialog_box_renderer.set_current_page_text_with_formatting(page_text);
      dialog_box_renderer.set_age(age);
      dialog_box_renderer.set_num_revealed_characters(num_revealed_characters);
      if (num_revealed_characters >= page_text.size()) dialog_box_renderer.set_page_is_finished(true);

      AllegroFlare::Placement2D place{
         1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height()
      };

      clear();

      place.start_transform();
      dialog_box_renderer.render();
      place.restore_transform();

      al_flip_display();
      std::this_thread::sleep_for(std::chrono::microseconds(10000)); // add sleep for more obvious visual delay
   }
   al_flip_display();
}



////////////////



TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableWithOptionsRendererWithAllegroRenderingFixtureTest,
//TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChoiceRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__will_not_crash)
{
   std::string choice_box_prompt = "Are you making progress?";
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "Absolutely!", "GOTO A" },
     { "It would seem that I am", "GOTO B" },
     { "I think so?", "GOTO C" },
   };
   //AllegroFlare::Elements::DialogBoxes::Choice choice_dialog_box(choice_box_prompt, choice_options);
   AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions choice_dialog_box = build_dialog_box();
   choice_dialog_box.set_pages({ choice_box_prompt });
   //choice_dialog_box.set_speaker("Dr. Alice");
   
   choice_dialog_box.move_cursor_position_down();

   AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer choice_renderer(
   //AllegroFlare::Elements::DialogBoxRenderers::ChoiceRenderer choice_renderer(
      &get_font_bin_ref(),
      "[dummy-placeholder-for-current_page_text_with_formatting-which-should-not-be-used]",
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


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableWithOptionsRendererWithAllegroRenderingFixtureTest,
//TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChoiceRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__renders_elements_in_motion_when_revealing)
{
   //std::string choice_box_prompt = "Do you have any information about the whereabouts of the missing villagers?";
   //std::string choice_box_prompt = "Do you know anything regarding the whereabouts and well-being of the villagers "
                                   //"who mysteriously disappeared without a trace, leaving their loved "
                                   //"ones in anguish and uncertainty?";
   std::string choice_box_prompt = "Do you know anything regarding the whereabouts and well-being of the villagers "
                                   "who (em)mysteriously disappeared(/em) without a trace?";//, leaving their loved "
                                   //"ones in anguish and uncertainty?";
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
   AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions choice_dialog_box = build_dialog_box(
      "Bobby",
      { choice_box_prompt },
      choice_options
   );
   //choice_dialog_box.set_pages({ choice_box_prompt });
   //choice_dialog_box.set_options(choice_options);
   //AllegroFlare::Elements::DialogBoxes::Choice choice_dialog_box(choice_box_prompt, choice_options);
   //choice_dialog_box.initialize();

   choice_dialog_box.move_cursor_position_down();

   int passes = 120 * 5;
   int num_revealed_characters = 0;
   for (int i=0; i<passes; i++)
   {
      //num_revealed_characters++; // TODO: This should probably be removed?
      //num_revealed_characters = num_revealed_printable_characters();
      // Update
      choice_dialog_box.update();
      num_revealed_characters = choice_dialog_box.get_num_revealed_printable_characters();

      // Render
      AllegroFlare::Elements::DialogBoxRenderers::InterparsableWithOptionsRenderer choice_renderer(
      //AllegroFlare::Elements::DialogBoxRenderers::ChoiceRenderer choice_renderer(
         &get_font_bin_ref(),
         //choice_box_prompt,
         "[dummy-placeholder-for-current_page_text_with_formatting-which-should-not-be-used]",
         //&get_bitmap_bin_ref(),
         &choice_dialog_box
      );
      //choice_renderer.set_age(choice_dialog_box.infer_age());

      //choice_renderer.set_speaking_character_name("Princess");
      //choice_renderer.set_showing_speaking_character_name(true);
      choice_renderer.set_choice_dialog_box(&choice_dialog_box);
      //choice_renderer.set_current_page_text_with_formatting(page_text);
      //choice_renderer.set_age(age);
      choice_renderer.set_age(choice_dialog_box.infer_age());
      choice_renderer.set_num_revealed_characters(num_revealed_characters); // TODO: Is this needed?



      AllegroFlare::Placement2D place{ 1920/2, 1080/2, choice_renderer.get_width(), choice_renderer.get_height() };

      clear();
      place.start_transform();
      choice_renderer.render();
      place.restore_transform();
      al_flip_display();
   }

   SUCCEED();
}


/*
TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChoiceRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__with_a_selection_cursor_box_injected__will_render_it)
{
   //std::string choice_box_prompt = "Do you have any information about the whereabouts of the missing villagers?";
   //std::string choice_box_prompt = "Do you know anything regarding the whereabouts and well-being of the villagers "
                                   //"who mysteriously disappeared without a trace?"
   //std::vector<std::pair<std::string, std::string>> choice_options = {
     //{ "I saw some strange tracks leading deeper into the forest. They might be related.", "GOTO A" },
     //{ "I haven't seen anyone, but I heard eerie whispers in the dark last night.", "GOTO B" },
     //{ "I'm not from around here, so I don't have any information on the villagers.", "GOTO C" },
   //};
   std::string choice_box_prompt = "Are you making progress?";
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "Absolutely!", "GOTO A" },
     { "It would seem that I am", "GOTO B" },
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
                                   "who mysteriously disappeared without a trace?";
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
*/


