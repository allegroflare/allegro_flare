

#include <AllegroFlare/Elements/StoryboardPages/Text.hpp>



namespace AllegroFlare
{
namespace Elements
{
namespace StoryboardPages
{


Text::Text(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
{
}


Text::~Text()
{
}


void Text::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


std::string Text::run()
{
   return "Hello World!";
}
} // namespace StoryboardPages
} // namespace Elements
} // namespace AllegroFlare


