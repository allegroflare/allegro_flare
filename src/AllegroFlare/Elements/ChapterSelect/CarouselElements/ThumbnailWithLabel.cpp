

#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabel.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace ChapterSelect
{
namespace CarouselElements
{


ThumbnailWithLabel::ThumbnailWithLabel(std::string bitmap_filename, std::string label_text)
   : AllegroFlare::Elements::ChapterSelect::CarouselElements::Base(AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel::TYPE)
   , bitmap_filename(bitmap_filename)
   , label_text(label_text)
{
}


ThumbnailWithLabel::~ThumbnailWithLabel()
{
}


std::string ThumbnailWithLabel::get_bitmap_filename() const
{
   return bitmap_filename;
}


std::string ThumbnailWithLabel::get_label_text() const
{
   return label_text;
}




} // namespace CarouselElements
} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


