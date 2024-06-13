

#include <AllegroFlare/Elements/ChapterSelect/CarouselElementRenderers/ThumbnailWithLabelRenderer.hpp>

#include <allegro5/allegro_primitives.h>
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


ThumbnailWithLabelRenderer::ThumbnailWithLabelRenderer(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::Base(AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelRenderer::TYPE)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , thumbnail_image_identifier("[unset-thumbnail_image_identifier]")
   , label_text("[unset-label_text]")
   , padding_x(20)
   , padding_y(20)
   , label_y_gutter(30)
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


void ThumbnailWithLabelRenderer::set_padding_x(float padding_x)
{
   this->padding_x = padding_x;
}


void ThumbnailWithLabelRenderer::set_padding_y(float padding_y)
{
   this->padding_y = padding_y;
}


void ThumbnailWithLabelRenderer::set_label_y_gutter(float label_y_gutter)
{
   this->label_y_gutter = label_y_gutter;
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


float ThumbnailWithLabelRenderer::get_padding_x() const
{
   return padding_x;
}


float ThumbnailWithLabelRenderer::get_padding_y() const
{
   return padding_y;
}


float ThumbnailWithLabelRenderer::get_label_y_gutter() const
{
   return label_y_gutter;
}


void ThumbnailWithLabelRenderer::render()
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelRenderer::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelRenderer::render]: error: guard \"font_bin\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelRenderer::render]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelRenderer::render]: error: guard \"bitmap_bin\" not met");
   }
   ALLEGRO_BITMAP *image = obtain_thumbnail_image();
   ALLEGRO_FONT *label_font = obtain_label_font();
   float label_y_offset = al_get_bitmap_height(image) + label_y_gutter;
   float label_text_max_width = al_get_bitmap_width(image);
   float label_text_line_height = calculate_label_text_line_height();

   // Render the image
   al_draw_bitmap(image, padding_x, padding_y, 0);

   // Render the text
   al_draw_multiline_text(
         label_font,
         ALLEGRO_COLOR{1, 1, 1, 1},
         padding_x,
         padding_y + label_y_offset,
         label_text_max_width,
         label_text_line_height,
         ALLEGRO_ALIGN_LEFT,
         label_text.c_str()
      );
   return;
}

float ThumbnailWithLabelRenderer::calculate_width()
{
   return al_get_bitmap_width(obtain_thumbnail_image()) + padding_x * 2;
}

float ThumbnailWithLabelRenderer::calculate_height()
{
   // (Assume a single line of text. Excess elements would dangle off)
   return al_get_bitmap_height(obtain_thumbnail_image())
         + label_y_gutter
         + calculate_label_text_line_height()
         + padding_y * 2;
}

float ThumbnailWithLabelRenderer::calculate_label_text_line_height()
{
   return al_get_font_line_height(obtain_label_font());
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
      error_message << "[AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelRenderer::obtain_label_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelRenderer::obtain_label_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -46");
}


} // namespace CarouselElementRenderers
} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


