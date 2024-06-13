
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


TEST(AllegroFlare_Elements_DialogBoxes_ChoiceTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxes::Choice choice;
}


TEST(AllegroFlare_Elements_DialogBoxes_ChoiceTest, get_type__returns_the_expected_value)
{
   AllegroFlare::Elements::DialogBoxes::Choice choice;
   EXPECT_EQ("DialogBoxes/Choice", choice.get_type());
}


TEST(AllegroFlare_Elements_DialogBoxes_ChoiceTest, get_prompt_full_text__when_not_initialized__raises_an_exception)
{
   AllegroFlare::Elements::DialogBoxes::Choice choice;
   EXPECT_THROW_GUARD_ERROR(
      choice.get_prompt_full_text(),
      "AllegroFlare::Elements::DialogBoxes::Choice::get_prompt_full_text",
      "initialized"
   );
}


TEST(AllegroFlare_Elements_DialogBoxes_ChoiceTest, when_initialized_with_some_options__cursor_position_is_set_to_0)
{
   al_init();
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "One simple choice", "GOTO A" },
   };
   AllegroFlare::Elements::DialogBoxes::Choice choice("What will you do?", choice_options);
   choice.initialize();

   EXPECT_EQ(0, choice.get_cursor_position());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_ChoiceTest, move_cursor_position_up__when_options_are_empty__does_nothing)
{
   al_init();
   AllegroFlare::Elements::DialogBoxes::Choice choice;
   choice.initialize();

   choice.move_cursor_position_up();

   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_ChoiceTest, move_cursor_position_down__when_options_are_empty__does_nothing)
{
   al_init();
   AllegroFlare::Elements::DialogBoxes::Choice choice;
   choice.initialize();

   choice.move_cursor_position_down();

   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_ChoiceTest, move_cursor_position_down__increments_the_cursor_position)
{
   al_init();
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "Post a log", "GOTO A" },
     { "Keep coding", "GOTO B" },
     { "Drink more soylent", "GOTO C" },
   };
   AllegroFlare::Elements::DialogBoxes::Choice choice("What will you do?", choice_options);
   choice.initialize();

   choice.advance(); // TODO: Consider adding a separate "advance_to_selection"
   choice.move_cursor_position_down();
   EXPECT_EQ(1, choice.get_cursor_position());
   choice.move_cursor_position_down();
   EXPECT_EQ(2, choice.get_cursor_position());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_ChoiceTest, move_cursor_position_down__decrements_the_cursor_position)
{
   al_init();
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "Post a log", "GOTO A" },
     { "Keep coding", "GOTO B" },
     { "Drink more soylent", "GOTO C" },
   };
   AllegroFlare::Elements::DialogBoxes::Choice choice("What will you do?", choice_options);
   choice.initialize();

   choice.advance(); // TODO: Consider adding a separate "advance_to_selection"
   choice.move_cursor_position_down();
   choice.move_cursor_position_down();
   choice.move_cursor_position_up();
   EXPECT_EQ(1, choice.get_cursor_position());
   choice.move_cursor_position_up();
   EXPECT_EQ(0, choice.get_cursor_position());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_ChoiceTest,
   move_cursor_position_up__when_at_the_top_of_the_list_of_chioices__wraps_to_the_bottom)
{
   al_init();
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "Post a log", "GOTO A" },
     { "Keep coding", "GOTO B" },
     { "Drink more soylent", "GOTO C" },
   };
   AllegroFlare::Elements::DialogBoxes::Choice choice("What will you do?", choice_options);
   choice.initialize();

   choice.advance(); // TODO: Consider adding a separate "advance_to_selection"
   choice.move_cursor_position_up();
   EXPECT_EQ(2, choice.get_cursor_position());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_ChoiceTest,
   move_cursor_position_down__when_at_the_end_of_the_list_of_chioices__wraps_back_to_the_top)
{
   al_init();
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "Post a log", "GOTO A" },
     { "Keep coding", "GOTO B" },
     { "Drink more soylent", "GOTO C" },
   };
   AllegroFlare::Elements::DialogBoxes::Choice choice("What will you do?", choice_options);
   choice.initialize();

   choice.advance(); // TODO: Consider adding a separate "advance_to_selection"
   choice.move_cursor_position_down();
   choice.move_cursor_position_down();
   choice.move_cursor_position_down();
   EXPECT_EQ(0, choice.get_cursor_position());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_ChoiceTest,
   get_current_selection_text__with_no_options__returns_an_empty_string)
{
   // WILL SKIP FOR NOW
}


TEST(AllegroFlare_Elements_DialogBoxes_ChoiceTest,
   get_current_selection_value__with_no_options__returns_an_empty_string)
{
   // WILL SKIP FOR NOW
}


TEST(AllegroFlare_Elements_DialogBoxes_ChoiceTest,
   get_current_selection_text__returns_the_text_from_the_current_selection)
{
   al_init();
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "Post a log", "GOTO A" },
     { "Keep coding", "GOTO B" },
     { "Drink more soylent", "GOTO C" },
   };
   AllegroFlare::Elements::DialogBoxes::Choice choice("What will you do?", choice_options);
   choice.initialize();

   choice.advance(); // TODO: Consider adding a separate "advance_to_selection"

   EXPECT_EQ("Post a log", choice.get_current_selection_text());

   choice.move_cursor_position_down();
   EXPECT_EQ("Keep coding", choice.get_current_selection_text());

   choice.move_cursor_position_down();
   EXPECT_EQ("Drink more soylent", choice.get_current_selection_text());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_ChoiceTest,
   get_current_selection_value__returns_the_value_from_the_current_selection)
{
   al_init();
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "Post a log", "GOTO A" },
     { "Keep coding", "GOTO B" },
     { "Drink more soylent", "GOTO C" },
   };
   AllegroFlare::Elements::DialogBoxes::Choice choice("What will you do?", choice_options);
   choice.initialize();

   choice.advance(); // TODO: Consider adding a separate "advance_to_selection"

   EXPECT_EQ("GOTO A", choice.get_current_selection_value());

   choice.move_cursor_position_down();
   EXPECT_EQ("GOTO B", choice.get_current_selection_value());

   choice.move_cursor_position_down();
   EXPECT_EQ("GOTO C", choice.get_current_selection_value());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_ChoiceTest,
   get_options_labels__will_return_a_list_of_the_labels_only)
{
   al_init();
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "Post a log", "GOTO A" },
     { "Keep coding", "GOTO B" },
     { "Drink more soylent", "GOTO C" },
   };
   AllegroFlare::Elements::DialogBoxes::Choice choice("What will you do?", choice_options);
   choice.initialize();

   std::vector<std::string> expected_items = {
     "Post a log",
     "Keep coding",
     "Drink more soylent",
   };

   EXPECT_EQ(expected_items, choice.get_options_labels());
   al_uninstall_system();
}


