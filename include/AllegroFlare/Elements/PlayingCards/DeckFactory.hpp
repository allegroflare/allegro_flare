#pragma once


#include <AllegroFlare/Elements/PlayingCards/Deck.hpp>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace PlayingCards
      {
         class DeckFactory
         {
         private:

         protected:


         public:
            DeckFactory();
            ~DeckFactory();

            static AllegroFlare::Elements::PlayingCards::Deck generate_standard_52_card_deck();
         };
      }
   }
}



