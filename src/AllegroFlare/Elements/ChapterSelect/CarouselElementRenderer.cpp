

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


CarouselElementRenderer::CarouselElementRenderer()
{
}


CarouselElementRenderer::~CarouselElementRenderer()
{
}


void CarouselElementRenderer::render_ThumbnailWithLabel(AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel* element)
{
   AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelRenderer renderer;
   // TODO: Pass in elements to render
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
   static std::map<std::string, std::function<void()>> items_map = {
      { AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel::TYPE, [this, element](){
         AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel *as =
            static_cast<AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel*>(element);
         render_ThumbnailWithLabel(as);
      }},
      //{ "development_level", [this](){
         //create_development_level();
      //}},
   };
   //static const std::map<std::string, std::function> map = {
      //{ AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel::TYPE
   //std::map<std::string, int> = {
   //};
   //if (element->is_type(AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel::TYPE))
   //{
      //AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel *as =
         //static_cast<AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel*>(element);
      //render_ThumbnailWithLabel(as);
   //}
   //else
   //{
      //AllegroFlare::Logger::throw_unhandled_case(
            //"AllegroFlare::Elements::ChapterSelect::CarouselElementRenderer",
            //element->get_type()
         //);
   //}

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
         AllegroFlare::Logger::throw_unhandled_case(
               "AllegroFlare::Elements::ChapterSelect::CarouselElementRenderer",
               element->get_type()
         );
         // item not found
         //std::stringstream error_message;
         //error_message << "[CubeShooter::LevelFactory::load_level]: error: Cannot load the item with the identifier \""
                       //<< identifier << "\", it does not exist.";
         //throw std::runtime_error(error_message.str());
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


