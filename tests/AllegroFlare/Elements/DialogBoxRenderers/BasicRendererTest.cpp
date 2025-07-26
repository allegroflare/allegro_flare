
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#ifdef _WIN32
#define TEST_FIXTURE_FONT_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/fonts/"
#define TEST_FIXTURE_BITMAP_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/bitmaps/"
#else
#define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/fonts/"
#define TEST_FIXTURE_BITMAP_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/"
#endif

#include <AllegroFlare/Elements/DialogBoxRenderers/BasicRenderer.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithInteractionFixture.hpp>
#include <allegro5/allegro_primitives.h>
#include <chrono>
#include <thread>

class AllegroFlare_Elements_DialogBoxRenderers_BasicRendererTest : public ::testing::Test {};
class AllegroFlare_Elements_DialogBoxRenderers_BasicRendererWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};
class AllegroFlare_Elements_DialogBoxRenderers_BasicRendererWithInteractionFixtureTest
   : public AllegroFlare::Testing::WithInteractionFixture
{};



TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer you_got_an_item_renderer;
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__when_the_dialog_box_is_finished__renders_special_empty_text)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer dialog_box_renderer(&font_bin);
   dialog_box_renderer.set_current_page_text("This dialog is finished");
   dialog_box_renderer.set_is_finished(true);
   
   AllegroFlare::Placement2D place{ 1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height() };
   clear_neutral();
   //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
   place.start_transform();
   dialog_box_renderer.render();
   place.restore_transform();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__draws_multiline_dialog)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);

   std::string page_text =
      "This is some dialog test text. In this case, there's a lot of text that will need to fit on multiple lines.";
   AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer dialog_box_renderer(&font_bin);
   dialog_box_renderer.set_current_page_text(page_text);

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height() };
   clear_neutral();
   //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
   place.start_transform();
   dialog_box_renderer.render();
   place.restore_transform();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicRendererWithAllegroRenderingFixtureTest,
   render__will_show_a_reveal_animation_respecting_age)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);

   std::string page_text =
      "This is some dialog test text. In this case, there's a lot of text that will need to fit on multiple lines.";
   AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer dialog_box_renderer(&font_bin);
   dialog_box_renderer.set_current_page_text(page_text);

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height() };

   float started_at = al_get_time();
   for (int passes=0; passes<60; passes++)
   {
      float age = al_get_time() - started_at;
      dialog_box_renderer.set_age(age);

      clear_neutral();
      //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});

      place.start_transform();
      dialog_box_renderer.render();
      place.restore_transform();
      al_flip_display();

      sleep_for_frame();
   }
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__will_propertly_render_num_revealed_characters)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);

   std::string page_text = "Some test dialog text that will reveal characters sequentially when rendering.";

   int num_revealed_characters = 0;
   for (unsigned i=0; i<page_text.size(); i++)
   {
      num_revealed_characters++;

      AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer dialog_box_renderer(&font_bin);
      dialog_box_renderer.set_current_page_text(page_text);
      dialog_box_renderer.set_num_revealed_characters(num_revealed_characters);

      AllegroFlare::Placement2D place{
         1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height()
      };

      clear_neutral();
      //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      place.start_transform();
      dialog_box_renderer.render();
      place.restore_transform();

      //al_flip_display();
      //std::this_thread::sleep_for(std::chrono::microseconds(10000)); // add sleep for more obvious visual delay
   }
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__when_showing_the_speaking_character_is_true__will_render_the_name_as_expected)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);

   std::string page_text = "Some test dialog text that will reveal characters sequentially when rendering.";

   int num_revealed_characters = 0;
   float started_at = al_get_time();
   for (unsigned i=0; i<page_text.size(); i++)
   {
      num_revealed_characters++;
      float age = al_get_time() - started_at;

      AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer dialog_box_renderer(&font_bin);
      dialog_box_renderer.set_speaking_character_name("Princess");
      dialog_box_renderer.set_showing_speaking_character_name(true);
      dialog_box_renderer.set_current_page_text(page_text);
      dialog_box_renderer.set_age(age);
      dialog_box_renderer.set_num_revealed_characters(num_revealed_characters);

      AllegroFlare::Placement2D place{
         1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height()
      };

      clear_neutral();
      //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      place.start_transform();
      dialog_box_renderer.render();
      place.restore_transform();

      al_flip_display();
      std::this_thread::sleep_for(std::chrono::microseconds(10000)); // add sleep for more obvious visual delay
   }
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicRendererWithInteractionFixtureTest,
   will_spawn_with_a_reveal_animation)
{
   std::string page_text = "Some test dialog text that will reveal characters sequentially when rendering.";
   int num_revealed_characters = 0;

   float time_now = 0;
   float time_nudge = 1.0 / 15.0;

   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            clear();


            // Draw the subject
            num_revealed_characters++;
            float age = time_now;

            AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer dialog_box_renderer(&get_font_bin_ref());
            dialog_box_renderer.set_speaking_character_name("Princess");
            dialog_box_renderer.set_showing_speaking_character_name(true);
            dialog_box_renderer.set_current_page_text(page_text);
            dialog_box_renderer.set_age(age);
            dialog_box_renderer.set_num_revealed_characters(num_revealed_characters);

            AllegroFlare::Placement2D place{
               1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height()
            };

            place.start_transform();
            dialog_box_renderer.render();
            place.restore_transform();



            interactive_test_render_status();
            al_flip_display();
         }
         break;

         //// For example:
         //case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
         //{
            //std::cout << "[AllegroFlare_Elements_MultiListTestWithAllegroRenderingFixture]: INFO: "
                      //<< "Play sound effect event was emitted. "
                      //<< std::endl;
         //}
         //break;

         //// For example:
         case ALLEGRO_EVENT_KEY_DOWN:
         {
            //time_now += time_nudge
            //bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_RIGHT:
                  time_now += time_nudge;
               break;

               case ALLEGRO_KEY_LEFT:
                  time_now -= time_nudge;
               break;
            }
         }
         break;
      }
   }
}


