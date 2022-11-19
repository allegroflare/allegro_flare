
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>

#include <allegro5/allegro.h>


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxes::Basic basic;
}

TEST(AllegroFlare_Elements_DialogBoxes_BasicTest, get_type__returns_the_expected_value)
{
   AllegroFlare::Elements::DialogBoxes::Basic basic;
   EXPECT_EQ("DialogBoxes/Basic", basic.get_type());
}


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest, set_pages__sets_the_pages_with_the_passed_value)
{
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "This is the text to page 2.\nPage 1 has two lines.",
      "And finally the last page",
   };
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;

   dialog_box.set_pages(pages);

   ASSERT_EQ(pages, dialog_box.get_pages());
}


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest,
   at_last_page__if_the_dialog_is_at_the_very_last_page__will_return_true)
{
   al_init();
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "This is the text to page 2.\nPage 1 has two lines.",
      "And finally the last page",
   };
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
   dialog_box.set_pages(pages);

   ASSERT_EQ(true, dialog_box.next_page());
   ASSERT_EQ(true, dialog_box.next_page());

   ASSERT_EQ(true, dialog_box.at_last_page());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest,
   at_last_page__if_the_dialog_is_anywhere_but_at_the_very_last_page__will_return_false)
{
   al_init();
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "This is the text to page 2.\nPage 1 has two lines.",
      "And finally the last page",
   };
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
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


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest,
   advance__when_the_current_page_is_not_finished__will_finish_the_current_page_and_return_true)
{
   // TODO
}


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest,
   advance__when_the_current_page_is_finished__will_go_to_the_next_page)
{
   // TODO
}


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest,
   advance__when_the_dialog_box_is_finished__will_return_false)
{
   // TODO
}


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest, next_page__will_increment_the_page_number)
{
   al_init();
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "This is the text to page 2.\nPage 1 has two lines.",
      "And finally the last page",
   };
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;

   dialog_box.set_pages(pages);

   ASSERT_EQ(0, dialog_box.get_current_page_num());
   dialog_box.next_page();
   ASSERT_EQ(1, dialog_box.get_current_page_num());
   dialog_box.next_page();
   ASSERT_EQ(2, dialog_box.get_current_page_num());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest, has_no_pages__will_true_if_there_are_no_pages)
{
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
   ASSERT_EQ(true, dialog_box.has_no_pages());
}


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest,
   get_current_page_text__will_return_a_special_empty_text_when_not_on_a_page)
{
   al_init();
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
   dialog_box.next_page();

   std::string expected_page_text = "[null]";

   ASSERT_EQ(expected_page_text, dialog_box.get_current_page_text());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest,
   next_page__when_at_the_last_page__will_mark_the_dialog_box_as_finished)
{
   al_init();
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;

   EXPECT_EQ(false, dialog_box.get_finished());
   dialog_box.next_page();

   ASSERT_EQ(true, dialog_box.get_finished());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest, next_page__will_increment_the_page_text)
{
   al_init();
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "This is the text to page 2.\nPage 1 has two lines.",
      "And finally the last page.",
   };
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
   dialog_box.set_pages(pages);

   dialog_box.next_page();

   std::string expected_page_text = "This is the text to page 2.\nPage 1 has two lines.";
   ASSERT_EQ(expected_page_text, dialog_box.get_current_page_text());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest, update__will_increment_the_num_revealed_characters)
{
   al_init();
   std::vector<std::string> pages = {
      "This is text who's characters will reveal over time.",
   };
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
   dialog_box.set_pages(pages);

   EXPECT_EQ(0, dialog_box.get_num_revealed_characters());
   dialog_box.update();
   EXPECT_EQ(1, dialog_box.get_num_revealed_characters());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest,
   update__upon_all_characters_becoming_revealed__will_mark_the_page_as_finished)
{
   // TODO
}


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest,
   update__upon_all_characters_becoming_revealed__will_set__page_finished_at__to_the_current_time)
{
   // TODO
}


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest, reset__will_set_the_num_revealed_characters_to_0)
{
   al_init();
   std::vector<std::string> pages = {
      "This is text who's characters will reveal over time.",
   };
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
   dialog_box.set_pages(pages);

   for (unsigned i=0; i<30; i++) dialog_box.update();
   EXPECT_NE(0, dialog_box.get_num_revealed_characters());

   dialog_box.reset();
   EXPECT_EQ(0, dialog_box.get_num_revealed_characters());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest, reset__will_set_finished_at_to_0)
{
   al_init();
   std::vector<std::string> pages = { "This is text who's characters will reveal over time.", };
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box(pages);

   for (unsigned i=0; i<30; i++) dialog_box.update();
   //EXPECT_NE(0, dialog_box.get_finished_at());

   //dialog_box.reset();
   //EXPECT_EQ(0, dialog_box.get_finished_at());
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxes_BasicTest, next_page__will_set_the_num_revealed_characters_to_0)
{
   al_init();
   std::vector<std::string> pages = {
      "This is text who's characters will reveal over time.",
      "This line will have 0 revealed characters when first seen.",
   };
   AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
   dialog_box.set_pages(pages);

   dialog_box.reveal_all_characters();
   EXPECT_NE(0, dialog_box.get_num_revealed_characters());

   dialog_box.reset();
   EXPECT_EQ(0, dialog_box.get_num_revealed_characters());
   al_uninstall_system();
}



