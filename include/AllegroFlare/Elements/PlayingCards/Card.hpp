#pragma once




namespace AllegroFlare
{
   namespace Elements
   {
      namespace PlayingCards
      {
         class Card
         {
         private:
            int value;
            int suit;

         public:
            Card(int value=0, int suit=0);
            ~Card();

         };
      }
   }
}



