#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class ScrollBar
      {
      private:
         std::string quote;

      public:
         ScrollBar();
         ~ScrollBar();

         void render();
      };
   }
}



