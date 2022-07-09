

#include <AllegroFlare/StoryboardFactory.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Text.hpp>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{


StoryboardFactory::StoryboardFactory(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
{
}


StoryboardFactory::~StoryboardFactory()
{
}


void StoryboardFactory::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void StoryboardFactory::create_text_page(std::string text)
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "StoryboardFactory" << "::" << "create_text_page" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return new AllegroFlare::Elements::StoryboardPages::Text(&font_bin, text);
   return;
}
} // namespace AllegroFlare


