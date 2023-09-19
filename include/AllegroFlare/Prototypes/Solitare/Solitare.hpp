#pragma once


#include <AllegroFlare/Elements/PlayingCards/Card.hpp>
#include <AllegroFlare/Elements/PlayingCards/Deck.hpp>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Solitare
      {
         class Solitare
         {
         private:
            AllegroFlare::Elements::PlayingCards::Deck stock;
            AllegroFlare::Elements::PlayingCards::Deck waste;
            std::vector<std::vector<std::tuple<bool, AllegroFlare::Elements::PlayingCards::Card>>> tableau;
            std::vector<std::vector<AllegroFlare::Elements::PlayingCards::Deck>> foundations;
            std::string state;
            void deal_cards();
            void set_state_playing();
            void check_game_win_or_lose();
            void set_state_game_won();
            void set_state_game_lost();

         protected:


         public:
            Solitare();
            ~Solitare();

            AllegroFlare::Elements::PlayingCards::Deck get_stock() const;
            AllegroFlare::Elements::PlayingCards::Deck get_waste() const;
            std::vector<std::vector<std::tuple<bool, AllegroFlare::Elements::PlayingCards::Card>>> get_tableau() const;
            std::vector<std::vector<AllegroFlare::Elements::PlayingCards::Deck>> get_foundations() const;
            void start();
            void flip_topmost_card_on_tableau_column_to_face_up(int tableau_column_num=0);
            void place_top_stock_card_on_waste();
            void place_top_waste_card_on_foundation(int foundation_index_num=0);
            void replenish_stock_with_waste();
            void move_cards_from_tableau_column_to_other_tableau_column(int source_tableau_column_num=0, int destination_tableau_column_num=0, int num_cards_from_topmost_card=0);
            void move_topmost_tableau_column_card_to_foundation(int tableau_column_num=0);
            int stock_num_cards();
         };
      }
   }
}



