

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
   , label_text("[unset-label_text]")
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


void ThumbnailWithLabelRenderer::set_label_text(std::string label_text)
{
   this->label_text = label_text;
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


std::string ThumbnailWithLabelRenderer::get_label_text() const
{
   return label_text;
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
   ALLEGRO_BITMAP *image = obtain_thumbnail_image();
   ALLEGRO_FONT *label_font = obtain_label_font();
   float label_y_offset = al_get_bitmap_height(image) + 30;
   float label_text_max_width = 476;
   float label_text_line_height = al_get_font_line_height(label_font);

   // Render the image
   al_draw_bitmap(image, 0, 0, 0);

   // Render the text
   al_draw_multiline_text(
         label_font,
         ALLEGRO_COLOR{1, 1, 1, 1},
         0,
         label_y_offset,
         label_text_max_width,
         label_text_line_height,
         ALLEGRO_ALIGN_LEFT,
         label_text.c_str()
      );
   return;
}

ALLEGRO_BITMAP* ThumbnailWithLabelRenderer::obtain_thumbnail_image()
{
   return bitmap_bin->auto_get(thumbnail_image_identifier);
}

ALLEGRO_FONT* ThumbnailWithLabelRenderer::obtain_label_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[ThumbnailWithLabelRenderer::obtain_label_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ThumbnailWithLabelRenderer::obtain_label_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -26");
}


} // namespace CarouselElementRenderers
} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


