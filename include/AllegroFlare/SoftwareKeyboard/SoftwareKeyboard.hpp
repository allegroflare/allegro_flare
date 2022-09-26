#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/SoftwareKeyboard/KeyboardKey.hpp>
#include <AllegroFlare/Vec2D.hpp>
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
         AllegroFlare::Vec2D cursor_location;
         AllegroFlare::Vec2D cursor_size;
         bool initialized;
         bool show_rectangle_outline_on_keys;
         AllegroFlare::Placement2D keyboard_placement;
         std::string result_string;
         void update_cursor_location();
         bool key_exists(std::string identifier="[unset-identifier]");
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         SoftwareKeyboard(AllegroFlare::FontBin* font_bin=nullptr, std::string font_name="Inter-Medium.ttf", int font_size=-54);
         ~SoftwareKeyboard();

         void set_font_name(std::string font_name);
         void set_font_size(int font_size);
         void set_result_string(std::string result_string);
         AllegroFlare::FontBin* get_font_bin() const;
         std::string get_font_name() const;
         int get_font_size() const;
         bool get_initialized() const;
         std::string get_result_string() const;
         std::unordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> &get_keys_ref();
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_keys(std::unordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> keys={});
         void initialize();
         void press_key_by_name(std::string name="[unset-name]");
         void increment_cursor_pos();
         void decrement_cursor_pos();
         void render();
         static std::unordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> build_boilerplate_keyboard_keys();
      };
   }
}



