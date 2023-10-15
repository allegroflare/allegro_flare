

#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabelUnlockable.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace ChapterSelect
{
namespace CarouselElements
{


ThumbnailWithLabelUnlockable::ThumbnailWithLabelUnlockable(std::string value, std::string bitmap_filename, std::string label_text, std::string locked_bitmap_filename, std::string locked_label_text, bool is_unlocked)
   : AllegroFlare::Elements::ChapterSelect::CarouselElements::Base(AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabelUnlockable::TYPE)
   , value(value)
   , bitmap_filename(bitmap_filename)
   , label_text(label_text)
   , locked_bitmap_filename(locked_bitmap_filename)
   , locked_label_text(locked_label_text)
   , is_unlocked(is_unlocked)
{
}


ThumbnailWithLabelUnlockable::~ThumbnailWithLabelUnlockable()
{
}


void ThumbnailWithLabelUnlockable::set_value(std::string value)
{
   this->value = value;
}


void ThumbnailWithLabelUnlockable::set_bitmap_filename(std::string bitmap_filename)
{
   this->bitmap_filename = bitmap_filename;
}


void ThumbnailWithLabelUnlockable::set_label_text(std::string label_text)
{
   this->label_text = label_text;
}


void ThumbnailWithLabelUnlockable::set_locked_bitmap_filename(std::string locked_bitmap_filename)
{
   this->locked_bitmap_filename = locked_bitmap_filename;
}


void ThumbnailWithLabelUnlockable::set_locked_label_text(std::string locked_label_text)
{
   this->locked_label_text = locked_label_text;
}


void ThumbnailWithLabelUnlockable::set_is_unlocked(bool is_unlocked)
{
   this->is_unlocked = is_unlocked;
}


std::string ThumbnailWithLabelUnlockable::get_value() const
{
   return value;
}


std::string ThumbnailWithLabelUnlockable::get_bitmap_filename() const
{
   return bitmap_filename;
}


std::string ThumbnailWithLabelUnlockable::get_label_text() const
{
   return label_text;
}


std::string ThumbnailWithLabelUnlockable::get_locked_bitmap_filename() const
{
   return locked_bitmap_filename;
}


std::string ThumbnailWithLabelUnlockable::get_locked_label_text() const
{
   return locked_label_text;
}


bool ThumbnailWithLabelUnlockable::get_is_unlocked() const
{
   return is_unlocked;
}




} // namespace CarouselElements
} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


