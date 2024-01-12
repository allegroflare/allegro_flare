#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace UI
      {
         class IntSpinner
         {
         public:

            enum State
            {
               STATE_UNDEF = 0,
               STATE_ENABLED,
               STATE_DISABLED,
               STATE_ACTIVE_FOCUS,
            };
         private:
            AllegroFlare::FontBin* font_bin;
            float x;
            float y;
            float width;
            float height;
            int font_size;
            int number;
            uint32_t state;
            bool state_is_busy;
            float state_changed_at;
            ALLEGRO_FONT* obtain_font(float _font_size=-34);

         protected:


         public:
            IntSpinner(AllegroFlare::FontBin* font_bin=nullptr, float x=0.0f, float y=0.0f, float width=130.0f, float height=60.0f, int font_size=-34);
            ~IntSpinner();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_x(float x);
            void set_y(float y);
            void set_width(float width);
            void set_height(float height);
            void set_font_size(int font_size);
            void set_number(int number);
            AllegroFlare::FontBin* get_font_bin() const;
            float get_x() const;
            float get_y() const;
            float get_width() const;
            float get_height() const;
            int get_font_size() const;
            int get_number() const;
            uint32_t get_state() const;
            void render();
            void draw_centered_text(std::string text="[unset-text]", float x=1920/2, float y=1080/3, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{0.0, 0.0, 0.0, 1.0}, float _font_size=-34);
            static void draw_triangle_right(float x=0.0f, float y=0.0f, float width=0.0f, float height=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
            static void draw_triangle_up(float x=0.0f, float y=0.0f, float width=0.0f, float height=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
            static void draw_triangle_down(float x=0.0f, float y=0.0f, float width=0.0f, float height=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
            void set_state(uint32_t state=STATE_UNDEF, bool override_if_busy=false);
            void update_state(float time_now=al_get_time());
            static bool is_valid_state(uint32_t state=STATE_UNDEF);
            bool is_state(uint32_t possible_state=STATE_UNDEF);
            float infer_current_state_age(float time_now=al_get_time());
         };
      }
   }
}



