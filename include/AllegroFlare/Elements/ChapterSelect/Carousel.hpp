#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <map>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         class Carousel
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements;
            int focused_element_position;
            std::map<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*, std::pair<float, float>> element_dimensions;
            AllegroFlare::Placement2D camera;

         protected:


         public:
            Carousel(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements={}, int focused_element_position=0);
            ~Carousel();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_focused_element_position(int focused_element_position);
            void set_camera(AllegroFlare::Placement2D camera);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> get_elements() const;
            int get_focused_element_position() const;
            AllegroFlare::Placement2D get_camera() const;
            void set_elements(std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements={});
            void rotate_carousel_left();
            void rotate_carousel_right();
            void reposition_camera_position_to_focused_element();
            void update();
            void render();
            float get_element_x_position_for(int position=0);
            void refresh_element_dimensions();
         };
      }
   }
}



