

#include <AllegroFlare/StoryboardPageFactory.hpp>

#include <AllegroFlare/Elements/StoryboardPages/Image.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Text.hpp>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


StoryboardPageFactory::StoryboardPageFactory(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
{
}


StoryboardPageFactory::~StoryboardPageFactory()
{
}


void StoryboardPageFactory::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


AllegroFlare::Elements::StoryboardPages::Text* StoryboardPageFactory::create_text_page(std::string text)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "StoryboardPageFactory" << "::" << "create_text_page" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   return new AllegroFlare::Elements::StoryboardPages::Text(font_bin, text);
}

AllegroFlare::Elements::StoryboardPages::AdvancingText* StoryboardPageFactory::create_advancing_text_page(std::string text)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "StoryboardPageFactory" << "::" << "create_advancing_text_page" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   return new AllegroFlare::Elements::StoryboardPages::AdvancingText(font_bin, text);
}

AllegroFlare::Elements::StoryboardPages::Image* StoryboardPageFactory::create_image_page(ALLEGRO_BITMAP* image)
{
   return new AllegroFlare::Elements::StoryboardPages::Image(image);
}


} // namespace AllegroFlare


