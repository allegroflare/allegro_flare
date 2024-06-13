
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxFactory.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <allegro5/allegro.h>


TEST(AllegroFlare_Elements_DialogBoxFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest, build_basic_test_dialog__without_allegro_initialized__throws_an_error)
{
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   EXPECT_THROW_GUARD_ERROR(
      dialog_factory.build_basic_test_dialog(),
      "AllegroFlare::Elements::DialogBoxFactory::build_basic_test_dialog",
      "al_is_system_installed()"
   );
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest,
   build_basic_test_dialog__returns_a_basic_dialog_with_some_filler_text)
{
   al_init(); // only for al_get_time, might replace with an AllegroFlare::Time class (could speed up/slow down time)
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   AllegroFlare::Elements::DialogBoxes::Basic basic_dialog_box;

   basic_dialog_box = dialog_factory.build_basic_test_dialog();

   std::vector<std::string> expected_pages = {
      { "Interesting.  I'm just sitting here working." },
      { "Oh well. I guess I'll just have to keep grinding." },
      { "At least I'm listening to some cool music." },
   };
   ASSERT_EQ(expected_pages, basic_dialog_box.get_pages());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest, create_basic_test_dialog__without_allegro_initialized__throws_an_error)
{
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   EXPECT_THROW_GUARD_ERROR(
      dialog_factory.create_basic_test_dialog(),
      "AllegroFlare::Elements::DialogBoxFactory::create_basic_test_dialog",
      "al_is_system_installed()"
   );
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest,
   create_basic_test_dialog__returns_a_basic_dialog_with_some_filler_text)
{
   al_init(); // only for al_get_time, might replace with an AllegroFlare::Time class (could speed up/slow down time)
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   AllegroFlare::Elements::DialogBoxes::Basic *basic_dialog_box  = dialog_factory.create_basic_test_dialog();

   std::vector<std::string> expected_pages = {
      { "Interesting.  I'm just sitting here working." },
      { "Oh well. I guess I'll just have to keep grinding." },
      { "At least I'm listening to some cool music." },
   };
   ASSERT_EQ(expected_pages, basic_dialog_box->get_pages());
   delete basic_dialog_box;
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest, build_basic_dialog__without_allegro_initialized__throws_an_error)
{
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   EXPECT_THROW_GUARD_ERROR(
      dialog_factory.build_basic_dialog(),
      "AllegroFlare::Elements::DialogBoxFactory::build_basic_dialog",
      "al_is_system_installed()"
   );
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest, build_basic_dialog__sets_the_lines_to_the_created_dialog)
{
   al_init(); // only for al_get_time, might replace with an AllegroFlare::Time class (could speed up/slow down time)

   std::string speaker = "Jonah";

   std::vector<std::string> pages = {
      { "This seems to be working." },
      { "Good thing I kept grinding." },
      { "I guess I didn't have to have the perfect answer in the beginning." },
   };
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   AllegroFlare::Elements::DialogBoxes::Basic created_dialog = dialog_factory.build_basic_dialog(speaker, pages);
   ASSERT_EQ(speaker, created_dialog.get_speaking_character());
   ASSERT_EQ(pages, created_dialog.get_pages());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest, create_basic_dialog__without_allegro_initialized__throws_an_error)
{
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   EXPECT_THROW_GUARD_ERROR(
      dialog_factory.create_basic_dialog(),
      "AllegroFlare::Elements::DialogBoxFactory::create_basic_dialog",
      "al_is_system_installed()"
   );
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest, create_basic_dialog__sets_the_lines_to_the_created_dialog)
{
   al_init(); // only for al_get_time, might replace with an AllegroFlare::Time class (could speed up/slow down time)
   std::string speaker = "Jonah";
   std::vector<std::string> pages = {
      { "This seems to be working." },
      { "Good thing I kept grinding." },
      { "I guess I didn't have to have the perfect answer in the beginning." },
   };
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   AllegroFlare::Elements::DialogBoxes::Basic* created_dialog = dialog_factory.create_basic_dialog(speaker, pages);
   delete created_dialog;
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest, create_choice_dialog__without_allegro_initialized__throws_an_error)
{
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   EXPECT_THROW_GUARD_ERROR(
      dialog_factory.create_choice_dialog(),
      "AllegroFlare::Elements::DialogBoxFactory::create_choice_dialog",
      "al_is_system_installed()"
   );
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest,
   create_choice_dialog__creates_a_choice_dialog__passes_the_arguments__and_initializes_it)
{
   al_init(); // only for al_get_time, might replace with an AllegroFlare::Time class (could speed up/slow down time)
   std::string speaker = "Jonah";
  std::string choice_prompt = "What will the test return?";
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "A passing test.", "GOTO A" },
     { "A failing test.", "GOTO B" },
   };
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   AllegroFlare::Elements::DialogBoxes::Choice* created_dialog = dialog_factory.create_choice_dialog(
         speaker,
         choice_prompt,
         choice_options
      );

   ASSERT_NE(nullptr, created_dialog);

   EXPECT_EQ(choice_prompt, created_dialog->get_prompt_full_text());
   EXPECT_EQ(choice_options, created_dialog->get_options());

   delete created_dialog;
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest, create_wait_dialog__without_allegro_initialized__throws_an_error)
{
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   EXPECT_THROW_GUARD_ERROR(
      dialog_factory.create_wait_dialog(),
      "AllegroFlare::Elements::DialogBoxFactory::create_wait_dialog",
      "al_is_system_installed()"
   );
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest, create_wait_dialog__creates_a_Wait_dialog_with_the_expected_values)
{
   al_init(); // only for al_get_time
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   AllegroFlare::Elements::DialogBoxes::Wait* created_dialog = dialog_factory.create_wait_dialog(1.25f);
   EXPECT_EQ(1.25f, created_dialog->get_duration());
   
   delete created_dialog;
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest,
   create_chapter_title_dialog__without_allegro_initialized__throws_an_error)
{
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   EXPECT_THROW_GUARD_ERROR(
      dialog_factory.create_chapter_title_dialog(),
      "AllegroFlare::Elements::DialogBoxFactory::create_chapter_title_dialog",
      "al_is_system_installed()"
   );
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest,
   create_chapter_title_dialog__creates_a_ChapterTitle_dialog_with_the_expected_values)
{
   al_init(); // only for al_get_time
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   AllegroFlare::Elements::DialogBoxes::ChapterTitle* created_dialog = dialog_factory.create_chapter_title_dialog(
         "Chapter 2: The Discovery",
         12.0f
      );
   EXPECT_EQ("Chapter 2: The Discovery", created_dialog->get_title_text());
   EXPECT_EQ(12.0f, created_dialog->get_duration());
   
   delete created_dialog;
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest,
   create_character_feature_dialog__without_allegro_initialized__throws_an_error)
{
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   EXPECT_THROW_GUARD_ERROR(
      dialog_factory.create_character_feature_dialog(),
      "AllegroFlare::Elements::DialogBoxFactory::create_character_feature_dialog",
      "al_is_system_installed()"
   );
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest,
   create_character_feature_dialog__creates_a_ChapterTitle_dialog_with_the_expected_values)
{
   al_init(); // only for al_get_time
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   AllegroFlare::Elements::DialogBoxes::CharacterFeature* created_dialog =
      dialog_factory.create_character_feature_dialog(
         "Dr. Cat",
         "A brilliant feline scientist, combines his sharp intellect and natural curiosity with scholarly zeal",
         "dr_cat_identifier.png",
         4.125f
      );
   EXPECT_EQ("Dr. Cat", created_dialog->get_character_name());
   EXPECT_EQ(
      "A brilliant feline scientist, combines his sharp intellect and natural curiosity with scholarly zeal",
      created_dialog->get_description()
   );
   EXPECT_EQ("dr_cat_identifier.png", created_dialog->get_character_image_identifier());
   EXPECT_EQ(4.125f, created_dialog->get_duration());
   
   delete created_dialog;
   al_uninstall_system();
}


