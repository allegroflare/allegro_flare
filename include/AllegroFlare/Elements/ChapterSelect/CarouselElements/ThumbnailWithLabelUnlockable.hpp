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
               std::string value;
               std::string bitmap_filename;
               std::string label_text;
               std::string locked_bitmap_filename;
               std::string locked_label_text;
               bool is_unlocked;

            protected:


            public:
               ThumbnailWithLabelUnlockable(std::string value="[unset-value]", std::string bitmap_filename="[unset-property]", std::string label_text="[unset-label_text]", std::string locked_bitmap_filename="[unset-locked_bitmap_filename]", std::string locked_label_text="[unset-locked_label_text]", bool is_unlocked=true);
               ~ThumbnailWithLabelUnlockable();

               std::string get_value() const;
               std::string get_bitmap_filename() const;
               std::string get_label_text() const;
               std::string get_locked_bitmap_filename() const;
               std::string get_locked_label_text() const;
               bool get_is_unlocked() const;
            };
         }
      }
   }
}



