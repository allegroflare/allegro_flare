

#include <AllegroFlare/Elements/ChapterSelect/CarouselElementRenderer.hpp>

#include <AllegroFlare/Elements/ChapterSelect/CarouselElementRenderers/ThumbnailWithLabelRenderer.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElementRenderers/ThumbnailWithLabelUnlockableRenderer.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabel.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabelUnlockable.hpp>
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


void CarouselElementRenderer::render(AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* element)
{
   if (!(element))
   {
      std::stringstream error_message;
      error_message << "[CarouselElementRenderer::render]: error: guard \"element\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CarouselElementRenderer::render: error: guard \"element\" not met");
   }
   render_or_calculate_dimensions(element, false);
   return;
}

std::pair<float, float> CarouselElementRenderer::calculate_dimensions(AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* element)
{
   if (!(element))
   {
      std::stringstream error_message;
      error_message << "[CarouselElementRenderer::calculate_dimensions]: error: guard \"element\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CarouselElementRenderer::calculate_dimensions: error: guard \"element\" not met");
   }
   return render_or_calculate_dimensions(element, true);
}

std::pair<float, float> CarouselElementRenderer::render_or_calculate_dimensions(AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* element, bool only_calculate_dimensions)
{
   if (!(element))
   {
      std::stringstream error_message;
      error_message << "[CarouselElementRenderer::render_or_calculate_dimensions]: error: guard \"element\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CarouselElementRenderer::render_or_calculate_dimensions: error: guard \"element\" not met");
   }
   std::pair<float, float> result_dimensions{0, 0}; 

   // TODO: See how to make this items_map static and not created at call-time for "render"
   std::map<std::string, std::function<void()>> items_map = {
      { AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel::TYPE, [
               this,
               element,
               only_calculate_dimensions,
               &result_dimensions
            ]() {
         AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel *as =
            static_cast<AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel*>(element);
         result_dimensions = render_or_calculate_dimensions_for__ThumbnailWithLabel(as, only_calculate_dimensions);
      }},
      { AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabelUnlockable::TYPE, [
               this,
               element,
               only_calculate_dimensions,
               &result_dimensions
            ]() {
         AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabelUnlockable *as =
            static_cast<AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabelUnlockable*>(element);
         result_dimensions = render_or_calculate_dimensions_for__ThumbnailWithLabelUnlockable(as, only_calculate_dimensions);
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

   return result_dimensions;
}

std::pair<float, float> CarouselElementRenderer::render_or_calculate_dimensions_for__ThumbnailWithLabel(AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel* element, bool only_calculate_dimensions)
{
   if (!(element))
   {
      std::stringstream error_message;
      error_message << "[CarouselElementRenderer::render_or_calculate_dimensions_for__ThumbnailWithLabel]: error: guard \"element\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CarouselElementRenderer::render_or_calculate_dimensions_for__ThumbnailWithLabel: error: guard \"element\" not met");
   }
   AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelRenderer renderer;
   renderer.set_bitmap_bin(bitmap_bin);
   renderer.set_font_bin(font_bin);
   renderer.set_thumbnail_image_identifier(element->get_bitmap_filename());
   renderer.set_label_text(element->get_label_text());

   if (!only_calculate_dimensions) renderer.render();

   std::pair<float, float> result{0, 0}; 

   if (only_calculate_dimensions)
   {
      result = { renderer.calculate_width(), renderer.calculate_height() };
   }

   return result;
}

std::pair<float, float> CarouselElementRenderer::render_or_calculate_dimensions_for__ThumbnailWithLabelUnlockable(AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabelUnlockable* element, bool only_calculate_dimensions)
{
   if (!(element))
   {
      std::stringstream error_message;
      error_message << "[CarouselElementRenderer::render_or_calculate_dimensions_for__ThumbnailWithLabelUnlockable]: error: guard \"element\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CarouselElementRenderer::render_or_calculate_dimensions_for__ThumbnailWithLabelUnlockable: error: guard \"element\" not met");
   }
   AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelUnlockableRenderer renderer;
   renderer.set_bitmap_bin(bitmap_bin);
   renderer.set_font_bin(font_bin);
   renderer.set_thumbnail_image_identifier(element->get_bitmap_filename());
   renderer.set_label_text(element->get_label_text());
   renderer.set_locked_thumbnail_image_identifier(element->get_locked_bitmap_filename());
   renderer.set_locked_label_text(element->get_locked_label_text());
   renderer.set_is_unlocked(element->get_is_unlocked());

   if (!only_calculate_dimensions) renderer.render();

   std::pair<float, float> result{0, 0}; 

   if (only_calculate_dimensions)
   {
      result = { renderer.calculate_width(), renderer.calculate_height() };
   }

   return result;
}


} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


