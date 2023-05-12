#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace StoryboardPages
      {
         class ImageWithAdvancingText : public AllegroFlare::Elements::StoryboardPages::Base
         {
         public:
            static constexpr char* DEFAULT_FONT_NAME = (char*)"Inter-Regular.ttf";
            static constexpr int DEFAULT_FONT_SIZE = -36;
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/StoryboardPages/ImageWithAdvancingText";

         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            std::string image_identifier;
            std::string text;
            AllegroFlare::Placement2D image_placement;
            std::string font_name;
            int font_size;
            ALLEGRO_COLOR text_color;
            float top_padding;
            float left_padding;
            float right_padding;
            float line_height_multiplier;
            float line_height_padding;
            float image_fade_in_duration_sec;
            int revealed_characters_count;
            float started_at;
            float all_characters_revealed_at;
            float wait_duration_after_all_characters_are_revealed;
            ALLEGRO_FONT* obtain_font();
            ALLEGRO_FONT* obtain_next_button_font();

         protected:


         public:
            ImageWithAdvancingText(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::string image_identifier="[unset-image_identifier]", std::string text="[unset-text]", AllegroFlare::Placement2D image_placement={1920 * 0.5, 1080 * 0.4, 1164, 500}, std::string font_name=DEFAULT_FONT_NAME, int font_size=DEFAULT_FONT_SIZE, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{1, 1, 1, 1}, float top_padding=720, float left_padding=380, float right_padding=380, float line_height_multiplier=1.4f, float line_height_padding=0.0f, float image_fade_in_duration_sec=1.5f);
            virtual ~ImageWithAdvancingText();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_image_identifier(std::string image_identifier);
            void set_text(std::string text);
            void set_image_placement(AllegroFlare::Placement2D image_placement);
            void set_font_name(std::string font_name);
            void set_font_size(int font_size);
            void set_text_color(ALLEGRO_COLOR text_color);
            void set_top_padding(float top_padding);
            void set_left_padding(float left_padding);
            void set_right_padding(float right_padding);
            void set_line_height_multiplier(float line_height_multiplier);
            void set_line_height_padding(float line_height_padding);
            void set_image_fade_in_duration_sec(float image_fade_in_duration_sec);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            std::string get_image_identifier() const;
            std::string get_text() const;
            AllegroFlare::Placement2D get_image_placement() const;
            std::string get_font_name() const;
            int get_font_size() const;
            ALLEGRO_COLOR get_text_color() const;
            float get_top_padding() const;
            float get_left_padding() const;
            float get_right_padding() const;
            float get_line_height_multiplier() const;
            float get_line_height_padding() const;
            float get_image_fade_in_duration_sec() const;
            int get_revealed_characters_count() const;
            float get_started_at() const;
            float get_all_characters_revealed_at() const;
            float get_wait_duration_after_all_characters_are_revealed() const;
            virtual void start() override;
            virtual void update() override;
            virtual void render() override;
            virtual void advance() override;
            std::string generate_revealed_text();
            void reveal_all_characters();
            void reveal_image();
            bool all_characters_are_revealed();
            float infer_age(float time_now=al_get_time());
         };
      }
   }
}



