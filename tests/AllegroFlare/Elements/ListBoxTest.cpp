
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/ListBox.hpp>


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


