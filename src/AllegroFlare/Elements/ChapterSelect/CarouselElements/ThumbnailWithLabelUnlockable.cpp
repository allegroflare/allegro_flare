

#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabelUnlockable.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace ChapterSelect
{
namespace CarouselElements
{


ThumbnailWithLabelUnlockable::ThumbnailWithLabelUnlockable(std::string bitmap_filename, std::string label_text, bool is_locked)
   : AllegroFlare::Elements::ChapterSelect::CarouselElements::Base(AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabelUnlockable::TYPE)
   , bitmap_filename(bitmap_filename)
   , label_text(label_text)
   , is_locked(is_locked)
{
}


ThumbnailWithLabelUnlockable::~ThumbnailWithLabelUnlockable()
{
}


std::string ThumbnailWithLabelUnlockable::get_bitmap_filename() const
{
   return bitmap_filename;
}


std::string ThumbnailWithLabelUnlockable::get_label_text() const
{
   return label_text;
}


bool ThumbnailWithLabelUnlockable::get_is_locked() const
{
   return is_locked;
}


void ThumbnailWithLabelUnlockable::lock()
{
   is_locked = true;
}

void ThumbnailWithLabelUnlockable::unlock()
{
   is_locked = false;
}


} // namespace CarouselElements
} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


