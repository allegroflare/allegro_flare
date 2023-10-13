#pragma once


#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         namespace CarouselElements
         {
            class ThumbnailWithLabel : public AllegroFlare::Elements::ChapterSelect::CarouselElements::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabel";

            private:
               std::string bitmap_filename;

            protected:


            public:
               ThumbnailWithLabel(std::string bitmap_filename="[unset-property]");
               virtual ~ThumbnailWithLabel();

               std::string get_bitmap_filename() const;
               virtual float calculate_width();
               virtual float calculate_height();
            };
         }
      }
   }
}



