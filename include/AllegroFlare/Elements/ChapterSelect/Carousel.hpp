#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/Base.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <map>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         class Carousel
         {
         public:
            static constexpr char* DEFAULT_FONT_IDENTIFIER = (char*)"Inter-Regular.ttf";
            static constexpr int DEFAULT_FONT_SIZE = -46;

         private:
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements;
            std::string rotate_carousel_sound_effect_identifier;
            std::string element_font_identifier;
            int element_font_size;
            int focused_element_position;
            std::map<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*, std::tuple<float, float, float, float>> element_dimensions;
            bool element_dimensions_refreshed;
            AllegroFlare::Placement2D camera;
            AllegroFlare::Placement2D camera_target;
            void emit_rotation_sound_effect();

         protected:


         public:
            Carousel(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::string element_font_identifier=DEFAULT_FONT_IDENTIFIER, int element_font_size=DEFAULT_FONT_SIZE);
            ~Carousel();

            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_rotate_carousel_sound_effect_identifier(std::string rotate_carousel_sound_effect_identifier);
            void set_element_font_identifier(std::string element_font_identifier);
            void set_element_font_size(int element_font_size);
            void set_camera(AllegroFlare::Placement2D camera);
            void set_camera_target(AllegroFlare::Placement2D camera_target);
            AllegroFlare::EventEmitter* get_event_emitter() const;
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> get_elements() const;
            std::string get_rotate_carousel_sound_effect_identifier() const;
            std::string get_element_font_identifier() const;
            int get_element_font_size() const;
            int get_focused_element_position() const;
            AllegroFlare::Placement2D get_camera() const;
            AllegroFlare::Placement2D get_camera_target() const;
            void set_elements(std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements={});
            int get_num_elements();
            void rotate_carousel_left();
            void rotate_carousel_right();
            void reposition_camera_position_to_focused_element();
            void update_camera_position();
            void update();
            void render();
            float get_element_x_position_for(int position=0);
            AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* get_element_at_position(int position=0);
            std::tuple<float, float, float, float> get_element_dimensions_at_position(int position=0);
            std::tuple<float, float, float, float> get_element_dimensions(AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* element=nullptr);
            void refresh_element_dimensions();
         };
      }
   }
}



