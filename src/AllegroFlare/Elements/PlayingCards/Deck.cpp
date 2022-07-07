

#include <AllegroFlare/Elements/PlayingCards/Deck.hpp>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{
namespace PlayingCards
{


Deck::Deck()
   : cards({})
{
}


Deck::~Deck()
{
}


std::vector<AllegroFlare::Elements::PlayingCards::Card> Deck::get_cards()
{
   return cards;
}


std::vector<AllegroFlare::Elements::PlayingCards::Card> &Deck::get_cards_ref()
{
   return cards;
}


void Deck::put_card_on_top(AllegroFlare::Elements::PlayingCards::Card card)
{
   cards.push_back(card);
   return;
}

void Deck::shuffle()
{
   std::random_device rd;
   std::mt19937 g(rd());

   std::shuffle(cards.begin(), cards.end(), g);
}

AllegroFlare::Elements::PlayingCards::Card Deck::draw_card()
{
   if (!((!cards.empty())))
      {
         std::stringstream error_message;
         error_message << "Deck" << "::" << "draw_card" << ": error: " << "guard \"(!cards.empty())\" not met";
         throw std::runtime_error(error_message.str());
      }
   AllegroFlare::Elements::PlayingCards::Card card = cards.back();
   cards.pop_back();
   return card;
}

bool Deck::empty()
{
   return cards.empty();
}

bool Deck::clear()
{
   cards.clear();
   return true;
}

int Deck::num_cards()
{
   return cards.size();
}
} // namespace PlayingCards
} // namespace Elements
} // namespace AllegroFlare


