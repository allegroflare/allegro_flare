#pragma once




namespace AllegroFlare
{
   namespace SoftwareKeyboard
   {
      class Key
      {
      private:
         char character;
         float x;
         float y;
         float width;
         float height;
         float last_pressed_at;

      protected:


      public:
         Key(char character='-', float x=0, float y=0, float width=0, float height=0, float last_pressed_at=0);
         ~Key();

         void set_character(char character);
         void set_x(float x);
         void set_y(float y);
         void set_width(float width);
         void set_height(float height);
         void set_last_pressed_at(float last_pressed_at);
         char get_character() const;
         float get_x() const;
         float get_y() const;
         float get_width() const;
         float get_height() const;
         float get_last_pressed_at() const;
      };
   }
}



