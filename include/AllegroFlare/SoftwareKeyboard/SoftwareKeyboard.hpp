#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/SoftwareKeyboard/KeyboardKey.hpp>
#include <allegro5/allegro_font.h>
#include <string>
#include <unordered_map>


namespace AllegroFlare
{
   namespace SoftwareKeyboard
   {
      class SoftwareKeyboard
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string font_name;
         int font_size;
         std::unordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> keys;
         int cursor_pos;
         bool initialized;
         void update_cursor_placement();
         bool key_exists(std::string identifier="[unset-identifier]");
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         SoftwareKeyboard(AllegroFlare::FontBin* font_bin=nullptr, std::string font_name="Inter-Medium.ttf", int font_size=-32);
         ~SoftwareKeyboard();

         void set_font_name(std::string font_name);
         void set_font_size(int font_size);
         AllegroFlare::FontBin* get_font_bin() const;
         std::string get_font_name() const;
         int get_font_size() const;
         bool get_initialized() const;
         std::unordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> &get_keys_ref();
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void initialize();
         void press_key_by_name(std::string name="[unset-name]");
         void increment_cursor_pos();
         void decrement_cursor_pos();
         void render();
         static std::unordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> build_boilerplate_keyboard_keys();
      };
   }
}



