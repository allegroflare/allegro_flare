#pragma once


#include <AllegroFlare/Elements/ChapterSelect/CarouselElementRenderers/Base.hpp>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         namespace CarouselElementRenderers
         {
            class ThumbnailWithLabelRenderer : public AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Elements/ChapterSelect/CarouselElementRenderers/ThumbnailWithLabelRenderer";

            private:

            protected:


            public:
               ThumbnailWithLabelRenderer();
               ~ThumbnailWithLabelRenderer();

               void render();
            };
         }
      }
   }
}



