
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/ListBox.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


static std::vector<std::pair<std::string, std::string>> build_food_test_data()
{
   return {
      { "Spinach Quiche", "quiche" },
      { "Vegetable Stir-Fry", "stir_fry" },
      { "Caprese Salad", "salad" },
      { "Mushroom Risotto", "risotto" },
      { "Eggplant Parmesan", "eggplant" },
      { "Vegetarian Chili", "chili" },
      { "Stuffed Bell Peppers", "stuffed_peppers" },
   };
}


TEST(AllegroFlare_Elements_ListBoxTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::ListBox list_box;
}


TEST(AllegroFlare_Elements_ListBoxTest, set_items__will_set_the_items)
{
   std::vector<std::pair<std::string, std::string>> test_items = build_food_test_data();
   AllegroFlare::Elements::ListBox list_box;
   list_box.set_items(test_items);
   EXPECT_EQ(7, list_box.num_items());
   EXPECT_EQ(test_items, list_box.get_items());
}


TEST(AllegroFlare_Elements_ListBoxTest, set_items__will_set_the_cursor_position_to_0)
{
   AllegroFlare::Elements::ListBox list_box;
   list_box.set_items(build_food_test_data());
   list_box.move_cursor_down();
   list_box.move_cursor_down();
   list_box.move_cursor_down();
   EXPECT_EQ(3, list_box.get_cursor_position());

   list_box.set_items(build_food_test_data());
   EXPECT_EQ(0, list_box.get_cursor_position());
}


TEST(AllegroFlare_Elements_ListBoxTest, get_item_labels__will_return_a_list_of_just_the_labels_for_the_items)
{
   AllegroFlare::Elements::ListBox list_box;
   list_box.set_items(build_food_test_data());

   std::vector<std::string> expected_item_labels = {
      "Spinach Quiche",
      "Vegetable Stir-Fry",
      "Caprese Salad",
      "Mushroom Risotto",
      "Eggplant Parmesan",
      "Vegetarian Chili",
      "Stuffed Bell Peppers",
   };

   EXPECT_EQ(expected_item_labels, list_box.get_item_labels());
}


TEST(AllegroFlare_Elements_ListBoxTest, set_cursor_position__will_set_the_cursor_position)
{
   AllegroFlare::Elements::ListBox list_box;
   list_box.set_items(build_food_test_data());
   list_box.set_cursor_position(3);
   EXPECT_EQ(3, list_box.get_cursor_position());
}


TEST(AllegroFlare_Elements_ListBoxTest, set_cursor_position__if_less_than_zero__will_throw_an_error)
{
   AllegroFlare::Elements::ListBox list_box;
   EXPECT_THROW_GUARD_ERROR(
      list_box.set_cursor_position(-1),
      "AllegroFlare::Elements::ListBox::set_cursor_position",
      "(cursor_position >= 0)"
   );
}


TEST(AllegroFlare_Elements_ListBoxTest,
   set_cursor_position__if_greater_than_or_equal_to_the_number_of_items__will_throw_an_error)
{
   AllegroFlare::Elements::ListBox list_box;
   list_box.set_items(build_food_test_data());
   int num_items = list_box.num_items();

   std::string expected_error_message = "[AllegroFlare::Elements::ListBox::set_cursor_position]: error: guard \"((cursor_position < "
                                        "items.size()) || (cursor_position == 0))\" not met";
    
   EXPECT_THROW_WITH_MESSAGE(list_box.set_cursor_position(num_items), std::runtime_error, expected_error_message);
   EXPECT_THROW_WITH_MESSAGE(list_box.set_cursor_position(num_items+1), std::runtime_error, expected_error_message);
}


