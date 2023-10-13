

#include <AllegroFlare/Elements/ChapterSelect/CarouselElementRenderer.hpp>

#include <AllegroFlare/Elements/ChapterSelect/CarouselElementRenderers/ThumbnailWithLabelRenderer.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabel.hpp>
#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace ChapterSelect
{


CarouselElementRenderer::CarouselElementRenderer(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
{
}


CarouselElementRenderer::~CarouselElementRenderer()
{
}


void CarouselElementRenderer::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void CarouselElementRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


AllegroFlare::BitmapBin* CarouselElementRenderer::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* CarouselElementRenderer::get_font_bin() const
{
   return font_bin;
}


void CarouselElementRenderer::render_ThumbnailWithLabel(AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel* element)
{
   if (!(element))
   {
      std::stringstream error_message;
      error_message << "[CarouselElementRenderer::render_ThumbnailWithLabel]: error: guard \"element\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CarouselElementRenderer::render_ThumbnailWithLabel: error: guard \"element\" not met");
   }
   AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelRenderer renderer;
   renderer.set_bitmap_bin(bitmap_bin);
   renderer.set_font_bin(font_bin);
   renderer.set_thumbnail_image_identifier(element->get_bitmap_filename());
   renderer.set_label_text(element->get_label_text());

   renderer.render();
   return;
}

void CarouselElementRenderer::render(AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* element)
{
   if (!(element))
   {
      std::stringstream error_message;
      error_message << "[CarouselElementRenderer::render]: error: guard \"element\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CarouselElementRenderer::render: error: guard \"element\" not met");
   }
   // TODO: See how to make this items_map static and not created at call-time for "render"
   std::map<std::string, std::function<void()>> items_map = {
      { AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel::TYPE, [this, element](){
         AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel *as =
            static_cast<AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel*>(element);
         render_ThumbnailWithLabel(as);
      }},
      //{ "development_level", [this](){
         //create_development_level();
      //}},
   };

   // locate and call the function to handle the item
   if (items_map.count(element->get_type()) == 0)
   {
      bool item_handled = false;
      //if (unrecognized_key_callback_func)
      //{
         //item_handled = unrecognized_key_callback_func();
      //}

      if (!item_handled)
      {
         // item not found
         AllegroFlare::Logger::throw_unhandled_case(
               "AllegroFlare::Elements::ChapterSelect::CarouselElementRenderer",
               element->get_type()
         );
      }
   }
   else
   {
      // call the item
      items_map[element->get_type()]();
   }

   return;
}


} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


