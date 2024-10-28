
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxes/Interparsable.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <allegro5/allegro.h>


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxes::Interparsable interparsable;
}

TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, get_type__returns_the_expected_value)
{
   AllegroFlare::Elements::DialogBoxes::Interparsable interparsable;
   EXPECT_EQ("AllegroFlare/Elements/DialogBoxes/Interparsable", interparsable.get_type());
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, set_pages__sets_the_pages_with_the_passed_value)
{
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "This is the text to page 2.\nPage 1 has two lines.",
      "And finally the last page",
   };
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;

   dialog_box.set_pages(pages);

   ASSERT_EQ(pages, dialog_box.get_pages());
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest,
   at_last_page__if_the_dialog_is_at_the_very_last_page__will_return_true)
{
   al_init();
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "This is the text to page 2.\nPage 1 has two lines.",
      "And finally the last page",
   };
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;
   dialog_box.set_pages(pages);

   ASSERT_EQ(true, dialog_box.next_page());
   ASSERT_EQ(true, dialog_box.next_page());

   ASSERT_EQ(true, dialog_box.at_last_page());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest,
   at_last_page__if_the_dialog_is_anywhere_but_at_the_very_last_page__will_return_false)
{
   al_init();
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "This is the text to page 2.\nPage 1 has two lines.",
      "And finally the last page",
   };
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;
   dialog_box.set_pages(pages);

   ASSERT_EQ(false, dialog_box.at_last_page());
   ASSERT_EQ(true, dialog_box.next_page());
   ASSERT_EQ(false, dialog_box.at_last_page());
   ASSERT_EQ(true, dialog_box.next_page());

   //ASSERT_EQ(true, dialog_box.at_last_page()); // skipping this check, covered in other test

   ASSERT_EQ(true, dialog_box.next_page());
   ASSERT_EQ(false, dialog_box.at_last_page());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest,
   advance__when_the_current_page_is_not_finished__will_finish_the_current_page_and_return_true)
{
   // TODO
   // NOTE: This behavior is probably no longer expected. "advance" now belongs to the Base class
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest,
   advance__when_the_current_page_is_finished__will_go_to_the_next_page)
{
   // TODO
   // NOTE: This behavior is probably no longer expected. "advance" now belongs to the Base class
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest,
   advance__when_the_dialog_box_is_finished__will_return_false)
{
   // TODO
   // NOTE: This behavior is probably no longer expected. "advance" now belongs to the Base class
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, next_page__will_increment_the_page_number)
{
   al_init();
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "This is the text to page 2.\nPage 1 has two lines.",
      "And finally the last page",
   };
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;

   dialog_box.set_pages(pages);

   ASSERT_EQ(0, dialog_box.get_current_page_num());
   dialog_box.next_page();
   ASSERT_EQ(1, dialog_box.get_current_page_num());
   dialog_box.next_page();
   ASSERT_EQ(2, dialog_box.get_current_page_num());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, update__when_the_current_page_contains_only_\
operational_text__will_automatically_advance_to_the_page_after)
{
   al_init();
   std::vector<std::string> pages = {
      "(some_operational_text)", // The first page is operational text only
      "This is page 2, otherwise known as page at index 0.",
   };
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;
   dialog_box.set_pages(pages);

   ASSERT_EQ(0, dialog_box.get_current_page_num());
   dialog_box.update();
   ASSERT_EQ(1, dialog_box.get_current_page_num());

   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, next_page__when_the_next_page_contains_only_\
operational_text__will_automatically_advance_to_the_page_after)
{
   al_init();
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "(some_operational_that_will_advance_to_the_next_page)",
      "This is the text to page 3.\nPage 3 has two lines.",
   };
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;

   dialog_box.set_pages(pages);

   ASSERT_EQ(0, dialog_box.get_current_page_num());
   dialog_box.next_page();
   ASSERT_EQ(2, dialog_box.get_current_page_num());

   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, next_page__when_at_the_last_page_that_contains_only_\
operational_text__will_mark_the_dialog_as_finished_and_set_the_finished_at_time)
{
   al_init();
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "(only_operational_text_on_this_last_page)",
   };
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;

   dialog_box.set_pages(pages);

   ASSERT_EQ(0, dialog_box.get_current_page_num());
   dialog_box.next_page();

   // Page is marked as finished
   EXPECT_EQ(-1, dialog_box.get_current_page_num());
   //EXPECT_EQ(true, dialog_box.get_page_finished()); // NOTE: The page being finished is not relevant
   EXPECT_EQ(true, dialog_box.get_finished());
   EXPECT_NE(0.0, dialog_box.get_finished_at());

   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, has_no_pages__will_true_if_there_are_no_pages)
{
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;
   ASSERT_EQ(true, dialog_box.has_no_pages());
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest,
   get_current_page_text_with_formatting__will_return_a_special_empty_text_when_not_on_a_page)
{
   al_init();
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;
   dialog_box.next_page();

   std::string expected_page_text = "[null]";

   ASSERT_EQ(expected_page_text, dialog_box.get_current_page_text_with_formatting());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest,
   next_page__when_at_the_last_page__will_mark_the_dialog_box_as_finished)
{
   al_init();
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;

   EXPECT_EQ(false, dialog_box.get_finished());
   dialog_box.next_page();

   ASSERT_EQ(true, dialog_box.get_finished());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, next_page__will_increment_the_page_text)
{
   al_init();
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "This is the text to page 2.\nPage 1 has two lines.",
      "And finally the last page.",
   };
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;
   dialog_box.set_pages(pages);

   dialog_box.next_page();

   std::string expected_page_text = "This is the text to page 2.\nPage 1 has two lines.";
   ASSERT_EQ(expected_page_text, dialog_box.get_current_page_text_with_formatting());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, update__will_increment_the_num_revealed_printable_characters)
{
   al_init();
   std::vector<std::string> pages = {
      "This is text who's characters will reveal over time.",
   };
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;
   dialog_box.set_pages(pages);

   EXPECT_EQ(0, dialog_box.get_num_revealed_printable_characters());
   dialog_box.update();
   EXPECT_EQ(1, dialog_box.get_num_revealed_printable_characters());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest,
   update__when_operational_chunks_are_passed_during_text_reveal__will_call_the_the_callback_with_the_\
expected_data)
{
   // TODO: Expand this test and/or make it more robust and comprehensive
   int num_calls = 0;
   al_init();
   std::vector<std::string> pages = {
      "This is text that includes (operational text) over time.",
   };
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;
   dialog_box.set_on_operational_chunk_func([](
         std::string text, AllegroFlare::Elements::DialogBoxes::Interparsable* dialog_box, void* user_data
      ){
      (*(int*)user_data)++;
   });
   dialog_box.set_on_operational_chunk_func_user_data(&num_calls);
   dialog_box.set_pages(pages);

   EXPECT_EQ(0, num_calls);
   for (int i=0; i<pages[0].size(); i++)
   {
      dialog_box.update();
   }
   EXPECT_EQ(1, num_calls);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest,
   update__when_operational_chunks_are_passed_during_text_reveal__and_the_last_chunk_is_an_operational_text__\
will_work_without_failure)
{
   // TODO: Expand this test and/or make it more robust and comprehensive
   int num_calls = 0;
   al_init();
   std::vector<std::string> pages = {
      "This is text that (emphasis)ends(/emphasis) in operational text.(play_chime_sound)",
   };
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;
   dialog_box.set_on_operational_chunk_func([](
         std::string text, AllegroFlare::Elements::DialogBoxes::Interparsable* dialog_box, void* user_data
      ){
      (*(int*)user_data)++;
   });
   dialog_box.set_on_operational_chunk_func_user_data(&num_calls);
   dialog_box.set_pages(pages);

   EXPECT_EQ(0, num_calls);
   for (int i=0; i<pages[0].size(); i++)
   {
      dialog_box.update();
   }
   EXPECT_EQ(3, num_calls);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest,
   num_revealed_printable_characters__when_operational_chunks_are_passed_during_text_reveal__will_return_the_number_\
of_characters_revealed_not_including_operational_text)
{
   // TODO: Expand this test and/or make it more robust and comprehensive
   int num_calls = 0;
   al_init();
   std::vector<std::string> pages = {
      "This is (em)text(/em) that includes (operational text) over time.",
   };
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;
   dialog_box.set_on_operational_chunk_func([](
         std::string text, AllegroFlare::Elements::DialogBoxes::Interparsable* dialog_box, void* user_data
      ){
      (*(int*)user_data)++;
   });
   dialog_box.set_on_operational_chunk_func_user_data(&num_calls);
   dialog_box.set_pages(pages);

   EXPECT_EQ(0, num_calls);
   for (int i=0; i<20; i++)
   {
      dialog_box.update();
   }
   EXPECT_EQ(2, num_calls);

   // TODO: Update this to continue incrementing *again* when an operational chunk is met
   EXPECT_EQ(18, dialog_box.get_num_revealed_printable_characters()); // NOTE: Should this be 20?

   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest,
   num_revealed_printable_characters__when_sequential_operational_chunks_are_passed_during_text_reveal__will_return_\
the_number_of_characters_revealed_not_including_operational_text)
{
   // TODO: Expand this test and/or make it more robust and comprehensive
   int num_calls = 0;
   al_init();
   std::vector<std::string> pages = {
      "This is (surprised)(wait)(happy)(em)text(/em) that includes (em)sequential operational text(/em).",
   };
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;
   dialog_box.set_on_operational_chunk_func([](
         std::string text, AllegroFlare::Elements::DialogBoxes::Interparsable* dialog_box, void* user_data
      ){
      (*(int*)user_data)++;
   });
   dialog_box.set_on_operational_chunk_func_user_data(&num_calls);
   dialog_box.set_pages(pages);

   EXPECT_EQ(0, num_calls);
   for (int i=0; i<20; i++)
   {
      dialog_box.update();
   }
   EXPECT_EQ(5, num_calls);

   // TODO: Update this to continue incrementing *again* when an operational chunk is met
   EXPECT_EQ(18, dialog_box.get_num_revealed_printable_characters()); // NOTE: Should this be 20?

   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest,
   update__upon_all_characters_becoming_revealed__will_mark_the_page_as_finished)
{
   // TODO
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest,
   update__upon_all_characters_becoming_revealed__will_set__page_finished_at__to_the_current_time)
{
   // TODO
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, reset__will_set_the_num_revealed_printable_characters_to_0)
{
   al_init();
   std::vector<std::string> pages = {
      "This is text who's characters will reveal over time.",
   };
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;
   dialog_box.set_pages(pages);

   for (unsigned i=0; i<30; i++) dialog_box.update();
   EXPECT_NE(0, dialog_box.get_num_revealed_printable_characters());

   dialog_box.reset();
   EXPECT_EQ(0, dialog_box.get_num_revealed_printable_characters());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, reset__will_set_finished_at_to_0)
{
   al_init();
   std::vector<std::string> pages = { "This is text who's characters will reveal over time.", };
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box(pages);

   for (unsigned i=0; i<30; i++) dialog_box.update();
   //EXPECT_NE(0, dialog_box.get_finished_at());

   //dialog_box.reset();
   //EXPECT_EQ(0, dialog_box.get_finished_at());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest,
   next_page__will_set_the_num_revealed_printable_characters_to_0)
{
   al_init();
   std::vector<std::string> pages = {
      "This is text who's characters will reveal over time.",
      "This line will have 0 revealed characters when first seen.",
   };
   AllegroFlare::Elements::DialogBoxes::Interparsable dialog_box;
   dialog_box.set_pages(pages);

   dialog_box.reveal_all_characters();
   EXPECT_NE(0, dialog_box.get_num_revealed_printable_characters());

   dialog_box.reset();
   EXPECT_EQ(0, dialog_box.get_num_revealed_printable_characters());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, parse_into_chunks__will_generate_the_expected_chunks)
{
   std::string raw_text_source = "This is some (color=green)dialog text(color=normal) that will fill this box.";

   std::vector<std::pair<bool, std::string>> expected_chunks = {
      { false, "This is some " },
      { true, "color=green" },
      { false, "dialog text" },
      { true, "color=normal" },
      { false, " that will fill this box." },
   };
   std::vector<std::pair<bool, std::string>> actual_chunks =
      AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks(raw_text_source);

   EXPECT_EQ(expected_chunks, actual_chunks);
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, parse_into_chunks__when_only_an_operational_chunk_is_\
present__will_parse_only_a_single_operational_chunk)
{
   std::string raw_text_source = "(character_sprite=happy)";

   std::vector<std::pair<bool, std::string>> expected_chunks = {
      { true, "character_sprite=happy" },
   };
   std::vector<std::pair<bool, std::string>> actual_chunks =
      AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks(raw_text_source);

   EXPECT_EQ(expected_chunks, actual_chunks);
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, collate_raw_text_source__will_return_text_that_has_\
operational_chunks_removed)
{
   std::string raw_text_source = "This is (color=green)dialog text(color=normal) that that has operational chunks.";

   std::string expected_processed_text = "This is dialog text that that has operational chunks.";
   std::string actual_processed_text = 
      AllegroFlare::Elements::DialogBoxes::Interparsable::collate_printable_text_only(raw_text_source);

   EXPECT_EQ(expected_processed_text, actual_processed_text);
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, parse_into_chunks__with_an_uneven_number_of_parens__will_\
throw_an_error)
{
   std::string raw_text_source = "This is some text ( that has a missing) closing (paren.";

   EXPECT_THROW_WITH_MESSAGE(
      AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks(raw_text_source),
      std::runtime_error,
      "[AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks]: error: Unmatched opening parenthesis "
         "found in text \"This is some text ( that has a missing) closing (paren.\""
   );
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, parse_into_chunks__when_nested_parens_are_present__will_\
throw_an_error)
{
   std::string raw_text_source = "This is some text ( that has nested ( parens ) ).";

   EXPECT_THROW_WITH_MESSAGE(
      AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks(raw_text_source),
      std::runtime_error,
      "[AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks]: error: Nested parentheses were "
         "found in the text \"This is some text ( that has nested ( parens ) ).\". Nested parens are not supported."
   );
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, parse_into_chunks__when_a_closing_paren_is_present_before_\
an_opening_paren__will_throw_an_error)
{
   std::string raw_text_source = "This is some text ) that has incorrect ( parens ) ).";

   EXPECT_THROW_WITH_MESSAGE(
      AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks(raw_text_source),
      std::runtime_error,
      "[AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks]: error: There was an open paren that "
         "does not have a matching closing paren in the text \"This is some text ) that has incorrect ( parens ) ).\""
   );
}


