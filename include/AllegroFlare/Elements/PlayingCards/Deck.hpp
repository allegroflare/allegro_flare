#pragma once


#include <AllegroFlare/Elements/PlayingCards/Card.hpp>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace PlayingCards
      {
         class Deck
         {
         private:
            std::vector<AllegroFlare::Elements::PlayingCards::Card> cards;

         public:
            Deck();
            ~Deck();

            std::vector<AllegroFlare::Elements::PlayingCards::Card> get_cards() const;
            std::vector<AllegroFlare::Elements::PlayingCards::Card> &get_cards_ref();
            void put_card_on_top(AllegroFlare::Elements::PlayingCards::Card card={});
            void shuffle();
            AllegroFlare::Elements::PlayingCards::Card draw_card();
            bool empty();
            bool clear();
            int num_cards();
         };
      }
   }
}



