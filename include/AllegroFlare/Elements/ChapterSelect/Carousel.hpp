#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <map>
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
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements;
            int focused_element_position;
            std::map<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*, std::tuple<float, float, float, float>> element_dimensions;
            bool element_dimensions_refreshed;
            AllegroFlare::Placement2D camera;
            AllegroFlare::Placement2D camera_target;

         protected:


         public:
            Carousel(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, int focused_element_position=0);
            ~Carousel();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_focused_element_position(int focused_element_position);
            void set_camera(AllegroFlare::Placement2D camera);
            void set_camera_target(AllegroFlare::Placement2D camera_target);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> get_elements() const;
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



