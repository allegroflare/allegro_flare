
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/PlayingCards/Deck.hpp>

TEST(AllegroFlare_Elements_PlayingCardsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::PlayingCards::Deck deck;
}

TEST(AllegroFlare_Elements_PlayingCardsTest, cards__initializs_to_empty)
{
   AllegroFlare::Elements::PlayingCards::Deck deck;
   ASSERT_EQ(true, deck.get_cards().empty());
}

TEST(AllegroFlare_Elements_PlayingCardsTest, put_card_on_top__will_place_a_card_on_the_deck)
{
   using AllegroFlare::Elements::PlayingCards::Card;
   AllegroFlare::Elements::PlayingCards::Deck deck;
   deck.put_card_on_top(Card());
   ASSERT_EQ(false, deck.get_cards().empty());
   ASSERT_EQ(1, deck.num_cards());
}

TEST(AllegroFlare_Elements_PlayingCardsTest, clear__will_remove_all_cards_from_the_deck)
{
   using AllegroFlare::Elements::PlayingCards::Card;
   AllegroFlare::Elements::PlayingCards::Deck deck;

   deck.put_card_on_top(Card());
   deck.put_card_on_top(Card());
   deck.put_card_on_top(Card());

   deck.clear();

   ASSERT_EQ(0, deck.num_cards());
}

TEST(AllegroFlare_Elements_PlayingCardsTest, shuffle__on_an_empty_deck_will_do_nothing)
{
   AllegroFlare::Elements::PlayingCards::Deck deck;
   deck.shuffle();
   SUCCEED();
}

TEST(AllegroFlare_Elements_PlayingCardsTest, shuffle__will_randomize_the_order_of_the_cards)
{
   // TODO
}

TEST(AllegroFlare_Elements_PlayingCardsTest, draw_card__will_return_the_last_card_in_the_deck__and_remove_it_from_the_deck)
{
   // TODO
}

TEST(AllegroFlare_Elements_PlayingCardsTest, draw_card__when_the_deck_empty__will_throw_an_error)
{
   // TODO
}

TEST(AllegroFlare_Elements_PlayingCardsTest, empty__will_return_true_if_there_are_no_more_cards_in_the_deck)
{
   // TODO
}

TEST(AllegroFlare_Elements_PlayingCardsTest, empty__will_return_false_if_there_card_in_the_deck)
{
   // TODO
}

TEST(AllegroFlare_Elements_PlayingCardsTest, num_cards__will_return_the_number_of_cards_in_the_deck)
{
   // TODO
}


