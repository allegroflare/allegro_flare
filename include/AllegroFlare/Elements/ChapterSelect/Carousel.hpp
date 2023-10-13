#pragma once


#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/Base.hpp>
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
            std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements;

         protected:


         public:
            Carousel(std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements={});
            ~Carousel();

            void set_elements(std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements);
            std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> get_elements() const;
            void update();
            void render();
         };
      }
   }
}



