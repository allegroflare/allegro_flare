
#include <gtest/gtest.h>

#include <Krampus21/DialogBoxes/Base.hpp>


class MyTestDialogBox : public Krampus21::DialogBoxes::Base
{
public:
   MyTestDialogBox() : Krampus21::DialogBoxes::Base("MyTestDialogBox") {}
};


TEST(Krampus21_DialogBoxes_BaseTest, type__when_not_from_a_derived_class__is_the_expected_default)
{
   std::string expected_type = "Base";
   Krampus21::DialogBoxes::Base base_dialog_box;
   ASSERT_EQ(expected_type, base_dialog_box.get_type());
}


TEST(Krampus21_DialogBoxes_BaseTest, can_be_created_without_blowing_up)
{
   Krampus21::DialogBoxes::Base base;
}


TEST(Krampus21_DialogBoxes_BaseTest, when_derived_the_type_of_the_derived_class_is_set)
{
   std::string expected_type = "MyTestDialogBox";
   MyTestDialogBox dialog_box;
   ASSERT_EQ(expected_type, dialog_box.get_type());
}


TEST(Krampus21_DialogBoxes_BaseTest, is_type__returns_true_if_the_type_matches_the_current_type)
{
   std::string the_type_that_it_is = "MyTestDialogBox";
   MyTestDialogBox dialog_box;
   ASSERT_EQ(true, dialog_box.is_type(the_type_that_it_is));
}


TEST(Krampus21_DialogBoxes_BaseTest, is_type__returns_false_if_the_type_does_not_matches_the_current_type)
{
   std::string some_type_that_it_is_not = "SomeTypeThatItIsNot";
   MyTestDialogBox dialog_box;
   ASSERT_EQ(false, dialog_box.is_type(some_type_that_it_is_not));
}


TEST(Krampus21_DialogBoxes_BaseTest, set_pages__sets_the_pages_with_the_passed_value)
{
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "This is the text to page 2.\nPage 1 has two lines.",
      "And finally the last page",
   };
   MyTestDialogBox dialog_box;

   dialog_box.set_pages(pages);

   ASSERT_EQ(pages, dialog_box.get_pages());
}


TEST(Krampus21_DialogBoxes_BaseTest, at_last_page__will_return_true_if_the_dialog_is_at_the_very_last_page)
{
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "This is the text to page 2.\nPage 1 has two lines.",
      "And finally the last page",
   };
   MyTestDialogBox dialog_box;
   dialog_box.set_pages(pages);

   ASSERT_EQ(true, dialog_box.next_page());
   ASSERT_EQ(true, dialog_box.next_page());

   ASSERT_EQ(true, dialog_box.at_last_page());
}


TEST(Krampus21_DialogBoxes_BaseTest, at_last_page__will_false_ff_the_dialog_is_anywhere_but_at_the_very_last_page)
{
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "This is the text to page 2.\nPage 1 has two lines.",
      "And finally the last page",
   };
   MyTestDialogBox dialog_box;
   dialog_box.set_pages(pages);

   ASSERT_EQ(false, dialog_box.at_last_page());
   ASSERT_EQ(true, dialog_box.next_page());
   ASSERT_EQ(false, dialog_box.at_last_page());
   ASSERT_EQ(true, dialog_box.next_page());

   //ASSERT_EQ(true, dialog_box.at_last_page()); // skipping this check, covered in other test

   ASSERT_EQ(true, dialog_box.next_page());
   ASSERT_EQ(false, dialog_box.at_last_page());
}


TEST(Krampus21_DialogBoxes_BaseTest, next_page__will_increment_the_page_number)
{
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "This is the text to page 2.\nPage 1 has two lines.",
      "And finally the last page",
   };
   MyTestDialogBox dialog_box;

   dialog_box.set_pages(pages);

   ASSERT_EQ(0, dialog_box.get_current_page_num());
   dialog_box.next_page();
   ASSERT_EQ(1, dialog_box.get_current_page_num());
   dialog_box.next_page();
   ASSERT_EQ(2, dialog_box.get_current_page_num());
}


TEST(Krampus21_DialogBoxes_BaseTest, has_no_pages__will_true_if_there_are_no_pages)
{
   MyTestDialogBox dialog_box;
   ASSERT_EQ(true, dialog_box.has_no_pages());
}


TEST(Krampus21_DialogBoxes_BaseTest, get_current_page_text__will_return_a_special_empty_text_when_not_on_a_page)
{
   MyTestDialogBox dialog_box;
   dialog_box.next_page();

   std::string expected_page_text = "[null]";

   ASSERT_EQ(expected_page_text, dialog_box.get_current_page_text());
}


TEST(Krampus21_DialogBoxes_BaseTest, next_page__when_at_the_last_page__will_mark_the_dialog_box_as_finished)
{
   MyTestDialogBox dialog_box;

   EXPECT_EQ(false, dialog_box.get_finished());
   dialog_box.next_page();

   ASSERT_EQ(true, dialog_box.get_finished());
}


TEST(Krampus21_DialogBoxes_BaseTest, next_page__will_increment_the_page_text)
{
   std::vector<std::string> pages = {
      "Page 1 has this test",
      "This is the text to page 2.\nPage 1 has two lines.",
      "And finally the last page.",
   };
   MyTestDialogBox dialog_box;
   dialog_box.set_pages(pages);

   dialog_box.next_page();

   std::string expected_page_text = "This is the text to page 2.\nPage 1 has two lines.";
   ASSERT_EQ(expected_page_text, dialog_box.get_current_page_text());
}


TEST(Krampus21_DialogBoxes_BaseTest, update__will_increment_the_num_revealed_characters)
{
   std::vector<std::string> pages = {
      "This is text who's characters will reveal over time.",
   };
   MyTestDialogBox dialog_box;
   dialog_box.set_pages(pages);

   EXPECT_EQ(0, dialog_box.get_num_revealed_characters());
   dialog_box.update();
   EXPECT_EQ(1, dialog_box.get_num_revealed_characters());
}


TEST(Krampus21_DialogBoxes_BaseTest, reset__will_set_the_num_revealed_characters_to_0)
{
   std::vector<std::string> pages = {
      "This is text who's characters will reveal over time.",
   };
   MyTestDialogBox dialog_box;
   dialog_box.set_pages(pages);

   for (unsigned i=0; i<30; i++) dialog_box.update();
   EXPECT_NE(0, dialog_box.get_num_revealed_characters());

   dialog_box.reset();
   EXPECT_EQ(0, dialog_box.get_num_revealed_characters());
}


TEST(Krampus21_DialogBoxes_BaseTest, next_page__will_set_the_num_revealed_characters_to_0)
{
   std::vector<std::string> pages = {
      "This is text who's characters will reveal over time.",
      "This line will have 0 revealed characters when first seen.",
   };
   MyTestDialogBox dialog_box;
   dialog_box.set_pages(pages);

   dialog_box.reveal_all_characters();
   EXPECT_NE(0, dialog_box.get_num_revealed_characters());

   dialog_box.reset();
   EXPECT_EQ(0, dialog_box.get_num_revealed_characters());
}



