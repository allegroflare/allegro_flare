
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/Prototypes/Solitare/Solitare.hpp>


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Solitare::Solitare solitare;
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest, stock__has_a_getter_and_is_initialized_as_empty)
{
   AllegroFlare::Prototypes::Solitare::Solitare solitare;
   ASSERT_EQ(0, solitare.stock_num_cards());
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest, start__will_create_7_piles_each_column_in_the_tableau)
{
   AllegroFlare::Prototypes::Solitare::Solitare solitare;
   solitare.start();
   std::vector<std::vector<std::tuple<bool, AllegroFlare::Elements::PlayingCards::Card>>> tableau =
      solitare.get_tableau();
   ASSERT_EQ(7, tableau.size());
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest,
   start__will_fill_each_column_in_the_tableau_with_the_expected_number_of_cards)
{
   AllegroFlare::Prototypes::Solitare::Solitare solitare;
   solitare.start();
   std::vector<std::vector<std::tuple<bool, AllegroFlare::Elements::PlayingCards::Card>>> tableau =
      solitare.get_tableau();
   ASSERT_EQ(7, tableau.size());

   for (unsigned i=0; i<7; i++)
   {
      std::vector<std::tuple<bool, AllegroFlare::Elements::PlayingCards::Card>> tableau_column = tableau[i];
      EXPECT_EQ(i+1, tableau_column.size());
   }
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest, start__has_the_expected_number_of_undelt_cards_in_the_stock)
{
   AllegroFlare::Prototypes::Solitare::Solitare solitare;
   solitare.start();
   ASSERT_EQ(24, solitare.stock_num_cards());
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest,
   start__will_set_all_the_cards_in_each_tableau_column_face_down_and_the_first_face_up)
{
   AllegroFlare::Prototypes::Solitare::Solitare solitare;
   solitare.start();
   std::vector<std::vector<std::tuple<bool, AllegroFlare::Elements::PlayingCards::Card>>> tableau =
      solitare.get_tableau();
   ASSERT_EQ(7, tableau.size());

   for (unsigned column=0; column<7; column++)
   {
      std::vector<std::tuple<bool, AllegroFlare::Elements::PlayingCards::Card>> tableau_column = tableau[column];

      ASSERT_EQ(false, tableau_column.empty());

      for (unsigned i=0; i<(tableau_column.size() - 1); i++)
      {
         std::tuple<bool, AllegroFlare::Elements::PlayingCards::Card> card = tableau_column[i];
         bool card_is_face_down = (std::get<0>(card) == false);
         EXPECT_EQ(true, card_is_face_down);
      }

      std::tuple<bool, AllegroFlare::Elements::PlayingCards::Card> &topmost_card =
         tableau_column[tableau_column.size()-1];
      bool card_is_face_up = (std::get<0>(topmost_card) == true);
      EXPECT_EQ(true, card_is_face_up);
   }
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest, start__will_create_4_empty_piles_for_the_foundations)
{
   AllegroFlare::Prototypes::Solitare::Solitare solitare;
   solitare.start();
   std::vector<std::vector<AllegroFlare::Elements::PlayingCards::Deck>> foundations = solitare.get_foundations();
   ASSERT_EQ(4, foundations.size());

   for (auto &foundation : foundations)
   {
      ASSERT_EQ(true, foundation.empty());
   }
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest, start__will_clear_the_waste)
{
   // TODO
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest, start__will_set_the_solitare_state_to_playing)
{
   // TODO
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest,
   flip_topmost_card_on_tableau_column_to_face_up__with_invalid_tableau_column_num__raises_an_error)
{
   AllegroFlare::Prototypes::Solitare::Solitare solitare;
   solitare.start();
   std::vector<int> invalid_column_nums = { -1, 99, -999, 7, 8 };
   for (auto &invalid_column_num : invalid_column_nums)
   {
      std::string expected_error_message = "invalid tableau_column_num";
      EXPECT_THROW_WITH_MESSAGE(
         solitare.flip_topmost_card_on_tableau_column_to_face_up(invalid_column_num),
         std::runtime_error,
         expected_error_message
      );
   }
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest,
   flip_topmost_card_on_tableau_column_to_face_up__on_a_column_that_is_empty__raises_an_error)
{
   // TODO
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest,
   flip_topmost_card_on_tableau_column_to_face_up__if_the_topmost_card_is_already_up__does_nothing)
{
   // TODO
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest,
   flip_topmost_card_on_tableau_column_to_face_up__flips_the_topmost_card_on_the_tableau_column)
{
   // TODO
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest,
   replenish_stock_with_waste__when_the_stock_is_not_empty__raises_an_error)
{
   // TODO
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest,
   replenish_stock_with_waste__when_the_waste_is_empty__raises_an_error)
{
   // TODO
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest,
   replenish_stock_with_waste__will_move_the_cards_from_the_waste_to_the_stock_preserving_order)
{
   // TODO
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest,
   move_topmost_tableau_row_to_foundation__with_an_invalid_tableau_column_num__raises_an_error)
{
   // TODO
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest,
   move_topmost_tableau_row_to_foundation__on_a_tableau_column_that_is_empty__raises_an_error)
{
   // TODO
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest,
   move_topmost_tableau_row_to_foundation__with_a_facedown_card_on_the_column__raises_an_error)
{
   // TODO
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest,
   move_topmost_tableau_row_to_foundation__will_remove_the_card_from_the_tableau_row)
{
   // TODO
}


TEST(AllegroFlare_Prototypes_Solitare_SolitareTest,
   move_topmost_tableau_row_to_foundation__will_add_the_topmost_card_to_the_foundation)
{
   // TODO
}


