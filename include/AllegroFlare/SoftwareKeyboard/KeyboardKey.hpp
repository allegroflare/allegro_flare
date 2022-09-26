#pragma once


#include <string>


namespace AllegroFlare
{
   namespace SoftwareKeyboard
   {
      class KeyboardKey
      {
      private:
         std::string character;
         float x;
         float y;
         float width;
         float height;
         float last_pressed_at;

      protected:


      public:
         KeyboardKey(std::string character="-", float x=0, float y=0, float width=0, float height=0);
         ~KeyboardKey();

         void set_character(std::string character);
         void set_x(float x);
         void set_y(float y);
         void set_width(float width);
         void set_height(float height);
         void set_last_pressed_at(float last_pressed_at);
         std::string get_character() const;
         float get_x() const;
         float get_y() const;
         float get_width() const;
         float get_height() const;
         float get_last_pressed_at() const;
         float get_x2();
         float get_y2();
      };
   }
}



