
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Elements/DialogBoxRenderer.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <chrono>
#include <thread>


// TODO: Update this test to use AllegroFlare/Testing/WithAllegroRenderingFixture


#ifdef _WIN32
#define TEST_FIXTURE_FONT_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/fonts/"
#define TEST_FIXTURE_BITMAP_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/bitmaps"
#else
#define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/fonts/"
#define TEST_FIXTURE_BITMAP_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps"
#endif

#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotAnItem.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotEvidence.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Wait.hpp>
#include <AllegroFlare/Elements/DialogBoxes/ChapterTitle.hpp>
#include <AllegroFlare/Elements/DialogBoxes/CharacterFeature.hpp>


TEST(AllegroFlare_Elements_DialogBoxRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer;
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest, render__when_allegro_is_not_installed__raises_an_exception)
{
   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer;
   std::string expected_error_message = "DialogBoxRenderer::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(dialog_box_renderer.render(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest,
   render__when_allegro_primitives_are_not_installed__raises_an_exception)
{
   al_init();

   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer;
   std::string expected_error_message =
      "DialogBoxRenderer::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   ASSERT_THROW_WITH_MESSAGE(dialog_box_renderer.render(), std::runtime_error, expected_error_message);

   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest, render__when_there_is_no_allegro_display__raises_an_exception)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer;

   std::string expected_error_message =
      "DialogBoxRenderer::render: error: guard \"al_get_current_display()\" not met";
   ASSERT_THROW_WITH_MESSAGE(dialog_box_renderer.render(), std::runtime_error, expected_error_message);

   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest,
   render__when_the_allegro_font_addon_has_not_been_initialized__raises_an_exception)
{
   al_init();
   al_init_primitives_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
   dialog_box.set_pages({ { "Some test dialog text." } });
   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(nullptr, nullptr, &dialog_box);

   std::string expected_error_message =
      "DialogBoxRenderer::render: error: guard \"al_is_font_addon_initialized()\" not met";
   ASSERT_THROW_WITH_MESSAGE(dialog_box_renderer.render(), std::runtime_error, expected_error_message);

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest,
   render__when_the_allegro_ttf_addon_has_not_been_initialized__raises_an_exception)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
   dialog_box.set_pages({ { "Some test dialog text." } });
   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(nullptr, nullptr, &dialog_box);

   std::string expected_error_message =
      "DialogBoxRenderer::render: error: guard \"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(dialog_box_renderer.render(), std::runtime_error, expected_error_message);

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest, render__when_there_is_no_font_bin__raises_an_exception)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
   dialog_box.set_pages({ { "Some test dialog text." } });
   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(nullptr, nullptr, &dialog_box);

   std::string expected_error_message =
      "DialogBoxRenderer::render: error: guard \"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(dialog_box_renderer.render(), std::runtime_error, expected_error_message);

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest, render__when_there_is_no_dialog_box__raises_an_exception)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(nullptr, &bitmap_bin);

   std::string expected_error_message =
      "DialogBoxRenderer::render: error: guard \"dialog_box\" not met";
   ASSERT_THROW_WITH_MESSAGE(dialog_box_renderer.render(), std::runtime_error, expected_error_message);

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest, render__draws_the_dialog_box)
{
   // TODO: Rename this test to include "DialogBoxes::Basic type dialog"
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   AllegroFlare::BitmapBin bitmap_bin;
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
   dialog_box.set_pages({ "Some test dialog text with multiple pages.", "Here's the second page." });
   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(&font_bin, &bitmap_bin, &dialog_box);

   dialog_box.reveal_all_characters();

   dialog_box_renderer.render();
   al_flip_display();
   //std::this_thread::sleep_for(std::chrono::seconds(1));

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest,
   render__draws_the_dialog_box_with_a_speaking_character_when_it_is_present)
{
   // TODO: Rename this test to include "DialogBoxes::Basic type dialog"
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   AllegroFlare::BitmapBin bitmap_bin;
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
   dialog_box.set_speaking_character("Daeums");
   dialog_box.set_pages({ "Some test dialog text with multiple pages.", "Here's the second page." });
   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(&font_bin, &bitmap_bin, &dialog_box);

   dialog_box.reveal_all_characters();

   dialog_box_renderer.render();
   al_flip_display();
   //std::this_thread::sleep_for(std::chrono::seconds(1));

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest,
   render__when_the_standard_dialog_box_font_name_is_changed__draws_the_dialog_box_as_expected)
{
   // TODO: Rename this test to include "DialogBoxes::Basic type dialog"
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   AllegroFlare::BitmapBin bitmap_bin;
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
   dialog_box.set_pages({ "Some test dialog text with multiple pages.", "Here's the second page." });

   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(&font_bin, &bitmap_bin, &dialog_box);
   dialog_box_renderer.set_standard_dialog_box_font_name("Lora-MediumItalic.ttf");

   dialog_box.reveal_all_characters();

   dialog_box_renderer.render();
   al_flip_display();
   //std::this_thread::sleep_for(std::chrono::seconds(1));

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest,
   render__when_the_standard_dialog_box_font_size_is_changed__draws_the_dialog_box_as_expected)
{
   // TODO: Rename this test to include "DialogBoxes::Basic type dialog"
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   AllegroFlare::BitmapBin bitmap_bin;
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
   dialog_box.set_pages({ "Some test dialog text with multiple pages.", "Here's the second page." });

   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(&font_bin, &bitmap_bin, &dialog_box);
   dialog_box_renderer.set_standard_dialog_box_font_size(-52);

   dialog_box.reveal_all_characters();

   dialog_box_renderer.render();
   al_flip_display();
   //std::this_thread::sleep_for(std::chrono::seconds(1));

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest, render__draws_a_choice_type_dialog_box)
{
   // TODO: Rename this test to include "DialogBoxes::Choice type dialog"
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   AllegroFlare::BitmapBin bitmap_bin;
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   AllegroFlare::Elements::DialogBoxes::Choice choice_dialog_box(
      "Hey! I'll just ask a simple question. What's up!?",
      {
         { "Not much", "NOTHING", },
         { "A lot", "EVERYTHING" },
      }
   );
   choice_dialog_box.initialize();
   //dialog_box.set_pages({ "Some test dialog text with multiple pages.", "Here's the second page." });
   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(&font_bin, &bitmap_bin, &choice_dialog_box);

   //choice_dialog_box.reveal_all_characters();

   dialog_box_renderer.render();
   al_flip_display();
   //std::this_thread::sleep_for(std::chrono::seconds(1));

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest,
   render__when_a_speaking_character_is_presnt__draws_a_choice_type_dialog_box_with_the_speaking_character)
{
   // TODO: Rename this test to include "DialogBoxes::Choice type dialog"
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   AllegroFlare::BitmapBin bitmap_bin;
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   AllegroFlare::Elements::DialogBoxes::Choice choice_dialog_box(
      "Hey! I'll just ask a simple question. What's up!?",
      {
         { "Not much", "NOTHING", },
         { "A lot", "EVERYTHING" },
      }
   );
   choice_dialog_box.set_speaking_character("Daeums");
   choice_dialog_box.initialize();
   //dialog_box.set_pages({ "Some test dialog text with multiple pages.", "Here's the second page." });
   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(&font_bin, &bitmap_bin, &choice_dialog_box);

   //choice_dialog_box.reveal_all_characters();

   dialog_box_renderer.render();
   al_flip_display();
   //std::this_thread::sleep_for(std::chrono::seconds(1));

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest,
   DISABLED__render__when_the_standard_dialog_box_font_name_is_changed__draws_the_choice_type_dialog_box_as_expected)
{
   // TODO
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest,
   DISABLED__render__when_the_standard_dialog_box_font_size_is_changed__draws_the_choice_type_dialog_box_as_expected)
{
   // TODO
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest, render__draws_a_you_got_an_item_type_dialog_box)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   AllegroFlare::BitmapBin bitmap_bin;
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   bitmap_bin.set_full_path(TEST_FIXTURE_BITMAP_FOLDER);
   AllegroFlare::Elements::DialogBoxes::YouGotAnItem you_got_an_item_dialog_box("Blaster", "blaster-02.png");
   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(&font_bin, &bitmap_bin, &you_got_an_item_dialog_box);

   dialog_box_renderer.render();
   al_flip_display();
   //std::this_thread::sleep_for(std::chrono::seconds(1));

   bitmap_bin.clear();
   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest, render__draws_a_YouGotEvidence_dialog_box)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   AllegroFlare::BitmapBin bitmap_bin;
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   bitmap_bin.set_full_path(TEST_FIXTURE_BITMAP_FOLDER);
   AllegroFlare::Elements::DialogBoxes::YouGotEvidence you_got_evidence_dialog_box(
      "Blaster",
      "evidence-placeholder-480x300.png"
   );
   you_got_evidence_dialog_box.set_created_at(-999);
   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(&font_bin, &bitmap_bin, &you_got_evidence_dialog_box);

   dialog_box_renderer.render();
   al_flip_display();
   //std::this_thread::sleep_for(std::chrono::seconds(1));

   bitmap_bin.clear();
   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest, render__draws_a_ChapterTitle_dialog_box)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   AllegroFlare::BitmapBin bitmap_bin;
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   bitmap_bin.set_full_path(TEST_FIXTURE_BITMAP_FOLDER);
   AllegroFlare::Elements::DialogBoxes::ChapterTitle chapter_title(
      "Chapter 2: The Emergence"
   );
   chapter_title.set_created_at(-999);
   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(&font_bin, &bitmap_bin, &chapter_title);

   dialog_box_renderer.render();
   al_flip_display();
   //std::this_thread::sleep_for(std::chrono::seconds(1));

   bitmap_bin.clear();
   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest, render__draws_a_CharacterFeature_dialog_box)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   AllegroFlare::BitmapBin bitmap_bin;
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   bitmap_bin.set_full_path(TEST_FIXTURE_BITMAP_FOLDER);
   AllegroFlare::Elements::DialogBoxes::CharacterFeature character_feature;
   character_feature.set_created_at(-999); // TODO: Consider a "middle-of-life" age
   character_feature.set_character_name("Dr. Cat");
   character_feature.set_description(
      "A brilliant feline scientist, combines his sharp intellect and natural curiosity with scholarly zeal"
   );
   character_feature.set_character_image_identifier("a_character_feature_image_identifier.png");
   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(&font_bin, &bitmap_bin, &character_feature);

   dialog_box_renderer.render();
   al_flip_display();
   //std::this_thread::sleep_for(std::chrono::seconds(1));

   bitmap_bin.clear();
   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest, render__will_handle_a_Wait_dialog_box)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   AllegroFlare::BitmapBin bitmap_bin;
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   bitmap_bin.set_full_path(TEST_FIXTURE_BITMAP_FOLDER);
   AllegroFlare::Elements::DialogBoxes::Wait wait(1.0f);
   wait.set_created_at(al_get_time());
   wait.initialize();

   AllegroFlare::Elements::DialogBoxRenderer dialog_box_renderer(&font_bin, &bitmap_bin, &wait);
   dialog_box_renderer.render();
   al_flip_display();
   //std::this_thread::sleep_for(std::chrono::seconds(1));

   bitmap_bin.clear();
   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxRendererTest, render__draws_a_basic_type_dialog_box)
{
   // TODO
}


