
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Elements/DialogBoxFactory.hpp>

#include <allegro5/allegro.h>


TEST(AllegroFlare_Elements_DialogBoxFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
}


TEST(AllegroFlare_Elements_DialogBoxFactoryTest, build_basic_test_dialog__without_allegro_initialized__throws_an_error)
{
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   std::string expected_error_message =
      "DialogBoxFactory::build_basic_test_dialog: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_factory.build_basic_test_dialog(), std::runtime_error, expected_error_message);
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
   std::string expected_error_message =
      "DialogBoxFactory::create_basic_test_dialog: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_factory.create_basic_test_dialog(), std::runtime_error, expected_error_message);
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
   std::string expected_error_message =
      "DialogBoxFactory::build_basic_dialog: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_factory.build_basic_dialog(), std::runtime_error, expected_error_message);
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
   std::string expected_error_message =
      "DialogBoxFactory::create_basic_dialog: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_factory.create_basic_dialog(), std::runtime_error, expected_error_message);
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
   std::string expected_error_message =
      "DialogBoxFactory::create_choice_dialog: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(dialog_factory.create_choice_dialog(), std::runtime_error, expected_error_message);
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


TEST(AllegroFlare_Elements_DialogBoxFactoryTest, create_wait_dialog__creates_a_Wait_dialog_with_the_expected_values)
{
   AllegroFlare::Elements::DialogBoxFactory dialog_factory;
   AllegroFlare::Elements::DialogBoxes::Wait* created_dialog = dialog_factory.create_wait_dialog(1.25f);
   EXPECT_EQ(1.25f, created_dialog->get_duration());
   
   delete created_dialog;
}


