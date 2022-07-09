#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <string>


namespace AllegroFlare
{
   class StoryboardFactory
   {
   private:
      AllegroFlare::FontBin* font_bin;

   public:
      StoryboardFactory(AllegroFlare::FontBin* font_bin=nullptr);
      ~StoryboardFactory();

      void set_font_bin(AllegroFlare::FontBin* font_bin);
      void create_text_page(std::string text="[unset-text]");
   };
}



