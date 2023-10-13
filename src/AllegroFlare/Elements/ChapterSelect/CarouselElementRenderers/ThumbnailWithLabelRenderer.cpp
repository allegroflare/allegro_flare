

#include <AllegroFlare/Elements/ChapterSelect/CarouselElementRenderers/ThumbnailWithLabelRenderer.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace ChapterSelect
{
namespace CarouselElementRenderers
{


ThumbnailWithLabelRenderer::ThumbnailWithLabelRenderer()
   : AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::Base(AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelRenderer::TYPE)
   , bitmap_bin(nullptr)
   , font_bin(nullptr)
   , thumbnail_image_identifier("[unset-thumbnail_image_identifier]")
{
}


ThumbnailWithLabelRenderer::~ThumbnailWithLabelRenderer()
{
}


void ThumbnailWithLabelRenderer::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void ThumbnailWithLabelRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void ThumbnailWithLabelRenderer::set_thumbnail_image_identifier(std::string thumbnail_image_identifier)
{
   this->thumbnail_image_identifier = thumbnail_image_identifier;
}


AllegroFlare::BitmapBin* ThumbnailWithLabelRenderer::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* ThumbnailWithLabelRenderer::get_font_bin() const
{
   return font_bin;
}


std::string ThumbnailWithLabelRenderer::get_thumbnail_image_identifier() const
{
   return thumbnail_image_identifier;
}


void ThumbnailWithLabelRenderer::render()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[ThumbnailWithLabelRenderer::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ThumbnailWithLabelRenderer::render: error: guard \"font_bin\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[ThumbnailWithLabelRenderer::render]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ThumbnailWithLabelRenderer::render: error: guard \"bitmap_bin\" not met");
   }
   return;
}


} // namespace CarouselElementRenderers
} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


