#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace StoryboardPages
      {
         class Text
         {
         private:
            AllegroFlare::FontBin* font_bin;

         public:
            Text(AllegroFlare::FontBin* font_bin=nullptr);
            ~Text();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            std::string run();
         };
      }
   }
}



