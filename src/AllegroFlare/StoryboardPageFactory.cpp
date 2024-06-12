

#include <AllegroFlare/StoryboardPageFactory.hpp>

#include <AllegroFlare/Elements/StoryboardPages/ClubCattLogo.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Image.hpp>
#include <AllegroFlare/Elements/StoryboardPages/ImageWithAdvancingText.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


StoryboardPageFactory::StoryboardPageFactory(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
{
}


StoryboardPageFactory::~StoryboardPageFactory()
{
}


void StoryboardPageFactory::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void StoryboardPageFactory::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void StoryboardPageFactory::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   this->model_bin = model_bin;
}


AllegroFlare::Elements::StoryboardPages::Text* StoryboardPageFactory::create_text_page(std::string text)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::StoryboardPageFactory::create_text_page]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::StoryboardPageFactory::create_text_page]: error: guard \"font_bin\" not met");
   }
   return new AllegroFlare::Elements::StoryboardPages::Text(font_bin, text);
}

AllegroFlare::Elements::StoryboardPages::AdvancingText* StoryboardPageFactory::create_advancing_text_page(std::string text)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::StoryboardPageFactory::create_advancing_text_page]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::StoryboardPageFactory::create_advancing_text_page]: error: guard \"font_bin\" not met");
   }
   return new AllegroFlare::Elements::StoryboardPages::AdvancingText(font_bin, text);
}

AllegroFlare::Elements::StoryboardPages::Image* StoryboardPageFactory::create_image_page(ALLEGRO_BITMAP* image)
{
   return new AllegroFlare::Elements::StoryboardPages::Image(image);
}

AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText* StoryboardPageFactory::create_image_with_advancing_text_page(std::string image_identifier, std::string text)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::StoryboardPageFactory::create_image_with_advancing_text_page]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::StoryboardPageFactory::create_image_with_advancing_text_page]: error: guard \"font_bin\" not met");
   }
   return new AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText(
      bitmap_bin,
      font_bin,
      image_identifier,
      text
   );
}

AllegroFlare::Elements::StoryboardPages::ClubCattLogo* StoryboardPageFactory::create_clubcatt_logo_page()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::StoryboardPageFactory::create_clubcatt_logo_page]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::StoryboardPageFactory::create_clubcatt_logo_page]: error: guard \"bitmap_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::StoryboardPageFactory::create_clubcatt_logo_page]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::StoryboardPageFactory::create_clubcatt_logo_page]: error: guard \"model_bin\" not met");
   }
   AllegroFlare::Elements::StoryboardPages::ClubCattLogo* result =
      new AllegroFlare::Elements::StoryboardPages::ClubCattLogo;
   result->set_bitmap_bin(bitmap_bin);
   result->set_model_bin(model_bin);
   result->initialize();
   return result;
}


} // namespace AllegroFlare


