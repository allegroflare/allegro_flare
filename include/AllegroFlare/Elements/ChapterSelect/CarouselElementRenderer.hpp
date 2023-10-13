#pragma once


#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/Base.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabel.hpp>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         class CarouselElementRenderer
         {
         private:

         protected:


         public:
            CarouselElementRenderer();
            ~CarouselElementRenderer();

            void render_ThumbnailWithLabel(AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel* element=nullptr);
            void render(AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* element=nullptr);
         };
      }
   }
}



