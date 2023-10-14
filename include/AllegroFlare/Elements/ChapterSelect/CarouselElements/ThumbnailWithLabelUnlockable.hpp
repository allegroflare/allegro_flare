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
            class ThumbnailWithLabelUnlockable : public AllegroFlare::Elements::ChapterSelect::CarouselElements::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabelUnlockable";

            private:
               std::string bitmap_filename;
               std::string label_text;
               bool is_locked;

            protected:


            public:
               ThumbnailWithLabelUnlockable(std::string bitmap_filename="[unset-property]", std::string label_text="[unset-label_text]", bool is_locked=true);
               ~ThumbnailWithLabelUnlockable();

               std::string get_bitmap_filename() const;
               std::string get_label_text() const;
               bool get_is_locked() const;
               void lock();
               void unlock();
            };
         }
      }
   }
}


