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
               std::string label_text;

            protected:


            public:
               ThumbnailWithLabel(std::string bitmap_filename="[unset-property]", std::string label_text="[unset-label_text]");
               ~ThumbnailWithLabel();

               std::string get_bitmap_filename() const;
               std::string get_label_text() const;
            };
         }
      }
   }
}



