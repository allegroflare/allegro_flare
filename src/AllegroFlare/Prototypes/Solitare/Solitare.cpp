

#include <AllegroFlare/Prototypes/Solitare/Solitare.hpp>

#include <AllegroFlare/Elements/PlayingCards/DeckFactory.hpp>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace Solitare
{


Solitare::Solitare()
   : stock({})
   , waste({})
   , tableau({})
   , foundations({})
   , state("playing")
{
}


Solitare::~Solitare()
{
}


AllegroFlare::Elements::PlayingCards::Deck Solitare::get_stock() const
{
   return stock;
}


AllegroFlare::Elements::PlayingCards::Deck Solitare::get_waste() const
{
   return waste;
}


std::vector<std::vector<std::tuple<bool, AllegroFlare::Elements::PlayingCards::Card>>> Solitare::get_tableau() const
{
   return tableau;
}


std::vector<std::vector<AllegroFlare::Elements::PlayingCards::Deck>> Solitare::get_foundations() const
{
   return foundations;
}


void Solitare::start()
{
   // Rules of solitare: https://bicyclecards.com/how-to-play/solitaire/

   stock = AllegroFlare::Elements::PlayingCards::DeckFactory::generate_standard_52_card_deck();
   stock.shuffle();

   tableau.clear();
   tableau.resize(7);

   waste.clear();

   foundations.clear();
   foundations.resize(4);

   deal_cards();

   set_state_playing();

   return;
}

void Solitare::flip_topmost_card_on_tableau_column_to_face_up(int tableau_column_num)
{
   // tableau_column_num must be valid
   if (tableau_column_num < 0 || tableau_column_num >= tableau.size())
   {
      throw std::runtime_error("invalid tableau_column_num");
   }

   // tableau column cannot be empty
   std::vector<std::tuple<bool, AllegroFlare::Elements::PlayingCards::Card>> &tableau_column =
      tableau[tableau_column_num];
   if (tableau_column.empty())
   {
      throw std::runtime_error("tableau_column is empty");
   }

   // if topmost card is already flipped up, just return
   std::tuple<bool, AllegroFlare::Elements::PlayingCards::Card> &topmost_card = tableau_column.back();

   // if topmost card is already flipped up, just return
   if (std::get<0>(topmost_card) == true) return;

   // flip the to face up
   std::get<0>(topmost_card) = true;

   return;
}

void Solitare::place_top_stock_card_on_waste()
{
   // if stock is empty, raise exception

   // TODO
   return;
}

void Solitare::place_top_waste_card_on_foundation(int foundation_index_num)
{
   // if waste is empty, raise exception
   // if top waste card does not fit onto any foundations, raise exception

   // TODO
   return;
}

void Solitare::replenish_stock_with_waste()
{
   // stock must be empty
   // waste must not be empty

   // TODO
   return;
}

void Solitare::move_cards_from_tableau_column_to_other_tableau_column(int source_tableau_column_num, int destination_tableau_column_num, int num_cards_from_topmost_card)
{
   // source_tableau_column_num must be valid
   // destination_tableau_column_num must be valid
   // num_cards_from_topmost_card must not exceed size of cards in tableau column
   // num_cards_from_topmost_card must be face up

   // TODO
   return;
}

void Solitare::move_topmost_tableau_column_card_to_foundation(int tableau_column_num)
{
   // tableau_column_num must be valid
   // tableau_column_num must not be empty
   // the topmost card in the tableau_column_num must be face-up

   // TODO
   return;
}

void Solitare::deal_cards()
{
   // deal the cards to all the columns
   for (unsigned column=0; column<tableau.size(); column++)
   {
      std::vector<std::tuple<bool, AllegroFlare::Elements::PlayingCards::Card>> &tableau_column = tableau[column];
      for (unsigned i=0; i<(column+1); i++)
      {
         AllegroFlare::Elements::PlayingCards::Card card_to_place_on_column = stock.draw_card();
         tableau_column.push_back(
               std::tuple<bool, AllegroFlare::Elements::PlayingCards::Card>(false, card_to_place_on_column)
            );
      }
   }

   // flip the first card on each column
   for (unsigned column=0; column<tableau.size(); column++)
   {
      flip_topmost_card_on_tableau_column_to_face_up(column);
   }
   return;
}

void Solitare::set_state_playing()
{
   state = "playing";
   return;
}

void Solitare::check_game_win_or_lose()
{
   // TODO
   return;
}

void Solitare::set_state_game_won()
{
   state = "game_won";
   return;
}

void Solitare::set_state_game_lost()
{
   state = "game_over";
   return;
}

int Solitare::stock_num_cards()
{
   return stock.num_cards();
}


} // namespace Solitare
} // namespace Prototypes
} // namespace AllegroFlare


