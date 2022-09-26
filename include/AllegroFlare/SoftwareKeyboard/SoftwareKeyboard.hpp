#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/SoftwareKeyboard/KeyboardKey.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace SoftwareKeyboard
   {
      class SoftwareKeyboard
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::vector<AllegroFlare::SoftwareKeyboard::KeyboardKey> keys;
         AllegroFlare::Vec2D cursor;

      protected:


      public:
         SoftwareKeyboard(AllegroFlare::FontBin* font_bin=nullptr);
         ~SoftwareKeyboard();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         AllegroFlare::FontBin* get_font_bin() const;
         std::string press_key();
         void render();
      };
   }
}



