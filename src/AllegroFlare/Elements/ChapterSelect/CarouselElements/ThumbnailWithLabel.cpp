

#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabel.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace ChapterSelect
{
namespace CarouselElements
{


ThumbnailWithLabel::ThumbnailWithLabel(std::string bitmap_filename)
   : AllegroFlare::Elements::ChapterSelect::CarouselElements::Base(AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel::TYPE)
   , bitmap_filename(bitmap_filename)
{
}


ThumbnailWithLabel::~ThumbnailWithLabel()
{
}


std::string ThumbnailWithLabel::get_bitmap_filename() const
{
   return bitmap_filename;
}


float ThumbnailWithLabel::calculate_width()
{
   return 0.0f;
}

float ThumbnailWithLabel::calculate_height()
{
   return 0.0f;
}


} // namespace CarouselElements
} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


