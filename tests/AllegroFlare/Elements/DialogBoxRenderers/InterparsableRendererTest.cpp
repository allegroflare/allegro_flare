
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxRenderers/InterparsableRenderer.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <allegro5/allegro_primitives.h>
#include <chrono>
#include <thread>

class AllegroFlare_Elements_DialogBoxRenderers_InterparsableRendererTest : public ::testing::Test {};
class AllegroFlare_Elements_DialogBoxRenderers_InterparsableRendererWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer you_got_an_item_renderer;
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__when_the_dialog_box_is_finished__renders_special_empty_text)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer dialog_box_renderer(&font_bin);
   dialog_box_renderer.set_current_page_text_with_formatting("This dialog is finished");
   dialog_box_renderer.set_is_finished(true);
   
   AllegroFlare::Placement2D place{ 1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height() };
   al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
   place.start_transform();
   dialog_box_renderer.render();
   place.restore_transform();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__draws_multiline_dialog)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();

   std::string page_text =
      "This is some dialog test text. In this case, there's a lot of text that will need to fit on multiple lines.";
   AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer dialog_box_renderer(&font_bin);
   dialog_box_renderer.set_current_page_text_with_formatting(page_text);

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height() };
   al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
   place.start_transform();
   dialog_box_renderer.render();
   place.restore_transform();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableRendererWithAllegroRenderingFixtureTest,
   FOCUS__CAPTURE__render__on_a_text_page_that_has_formatting_and_operational_tags_in_it__will_not_display_tags)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();

   std::string page_text =
      "This is dialog text that has (italic)some(/italic) formatting inside the source text. However, the "
      "formatting codes (bold)will(/bold) be removed when rendered.";
   AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer dialog_box_renderer(&font_bin);
   dialog_box_renderer.set_current_page_text_with_formatting(page_text);

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height() };
   al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
   place.start_transform();
   dialog_box_renderer.render();
   place.restore_transform();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableRendererWithAllegroRenderingFixtureTest,
   render__will_show_a_reveal_animation_respecting_age)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();

   std::string page_text =
      "This is some dialog test text. In this case, there's a lot of text that will need to fit on multiple lines.";
   AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer dialog_box_renderer(&font_bin);
   dialog_box_renderer.set_current_page_text_with_formatting(page_text);

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height() };

   float started_at = al_get_time();
   for (int passes=0; passes<60; passes++)
   {
      float age = al_get_time() - started_at;
      dialog_box_renderer.set_age(age);

      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});

      place.start_transform();
      dialog_box_renderer.render();
      place.restore_transform();
      al_flip_display();

      sleep_for_frame();
   }
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__will_propertly_render_num_revealed_characters)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();

   std::string page_text = "Some test dialog text that will reveal characters sequentially when rendering.";

   int num_revealed_characters = 0;
   for (unsigned i=0; i<page_text.size(); i++)
   {
      num_revealed_characters++;

      AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer dialog_box_renderer(&font_bin);
      dialog_box_renderer.set_current_page_text_with_formatting(page_text);
      dialog_box_renderer.set_num_revealed_characters(num_revealed_characters);

      AllegroFlare::Placement2D place{
         1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height()
      };

      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      place.start_transform();
      dialog_box_renderer.render();
      place.restore_transform();

      //al_flip_display();
      //std::this_thread::sleep_for(std::chrono::microseconds(10000)); // add sleep for more obvious visual delay
   }
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_InterparsableRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__when_showing_the_speaking_character_is_true__will_render_the_name_as_expected)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();

   std::string page_text = "Some test dialog text that will reveal characters sequentially when rendering.";

   int num_revealed_characters = 0;
   for (unsigned i=0; i<page_text.size(); i++)
   {
      num_revealed_characters++;

      AllegroFlare::Elements::DialogBoxRenderers::InterparsableRenderer dialog_box_renderer(&font_bin);
      dialog_box_renderer.set_speaking_character_name("Princess");
      dialog_box_renderer.set_showing_speaking_character_name(true);
      dialog_box_renderer.set_current_page_text_with_formatting(page_text);
      dialog_box_renderer.set_num_revealed_characters(num_revealed_characters);

      AllegroFlare::Placement2D place{
         1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height()
      };

      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      place.start_transform();
      dialog_box_renderer.render();
      place.restore_transform();

      //al_flip_display();
      //std::this_thread::sleep_for(std::chrono::microseconds(10000)); // add sleep for more obvious visual delay
   }
   al_flip_display();
}


