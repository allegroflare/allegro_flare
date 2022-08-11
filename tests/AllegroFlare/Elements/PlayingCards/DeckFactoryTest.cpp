
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/PlayingCards/DeckFactory.hpp>

TEST(AllegroFlare_Elements_PlayingCards_DeckFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::PlayingCards::DeckFactory deck_factory;
}

TEST(AllegroFlare_Elements_PlayingCards_DeckFactoryTest, generate_standard_52_card_deck)
{
   AllegroFlare::Elements::PlayingCards::Deck deck =
      AllegroFlare::Elements::PlayingCards::DeckFactory::generate_standard_52_card_deck();
   ASSERT_EQ(52, deck.num_cards());
}


