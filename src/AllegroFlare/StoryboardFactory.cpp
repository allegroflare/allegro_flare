

#include <AllegroFlare/StoryboardFactory.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Text.hpp>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/Elements/StoryboardPages/Text.hpp>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/Elements/StoryboardPages/Image.hpp>


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


AllegroFlare::Elements::StoryboardPages::Text* StoryboardFactory::create_text_page(std::string text)
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "StoryboardFactory" << "::" << "create_text_page" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return new AllegroFlare::Elements::StoryboardPages::Text(font_bin, text);
}

AllegroFlare::Elements::StoryboardPages::AdvancingText* StoryboardFactory::create_advancing_text_page(std::string text)
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "StoryboardFactory" << "::" << "create_advancing_text_page" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return new AllegroFlare::Elements::StoryboardPages::AdvancingText(font_bin, text);
}

AllegroFlare::Elements::StoryboardPages::Image* StoryboardFactory::create_image_page(ALLEGRO_BITMAP* image)
{
   return new AllegroFlare::Elements::StoryboardPages::Image(image);
}

AllegroFlare::Screens::StoryboardPlayer* StoryboardFactory::create_advancing_text_storyboard_screen(AllegroFlare::EventEmitter* event_emitter, std::vector<std::string> pages_text, int button_font_size, float page_top_padding, float page_left_padding, float page_right_padding, int page_text_font_size, float page_text_line_height_multiplier)
{
   AllegroFlare::Screens::StoryboardPlayer* result;

   // create the storyboard container
   result = new AllegroFlare::Screens::StoryboardPlayer(font_bin, event_emitter);
   result->initialize();

   // tweak the button styling
   AllegroFlare::Elements::StoryboardPlayer &storyboard_player_element = result->get_storyboard_element_ref();
   storyboard_player_element.set_button_font_size(button_font_size);

   // create all the pages
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages;
   for (auto &page_text : pages_text)
   {
      AllegroFlare::Elements::StoryboardPages::AdvancingText* advancing_text_page =
         create_advancing_text_page(page_text);
      advancing_text_page->set_top_padding(page_top_padding);
      advancing_text_page->set_left_padding(page_left_padding);
      advancing_text_page->set_right_padding(page_right_padding);
      advancing_text_page->set_font_size(page_text_font_size);
      advancing_text_page->set_line_height_multiplier(page_text_line_height_multiplier);
      pages.push_back(advancing_text_page);
   }
   storyboard_player_element.set_pages(pages);

   // return the result
   return result;
}
} // namespace AllegroFlare


