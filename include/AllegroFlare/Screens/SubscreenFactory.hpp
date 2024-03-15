#pragma once


#include <AllegroFlare/Screens/Subscreen/Screen.hpp>


namespace AllegroFlare
{
   namespace Screens
   {
      class SubscreenFactory
      {
      private:

      protected:


      public:
         SubscreenFactory();
         ~SubscreenFactory();

         AllegroFlare::Screens::Subscreen::Screen* create_basic_subscreen();
      };
   }
}



