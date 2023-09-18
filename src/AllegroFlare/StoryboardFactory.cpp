

#include <AllegroFlare/StoryboardFactory.hpp>

#include <AllegroFlare/Elements/StoryboardPages/AdvancingText.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Image.hpp>


namespace AllegroFlare
{


StoryboardFactory::StoryboardFactory()
   : bitmap_bin(nullptr)
   , font_bin(nullptr)
   , model_bin(nullptr)
   , event_emitter(nullptr)
   , page_factory()
{
}


StoryboardFactory::~StoryboardFactory()
{
}


void StoryboardFactory::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void StoryboardFactory::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
   page_factory.set_font_bin(font_bin);
   return;
}

void StoryboardFactory::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
   page_factory.set_bitmap_bin(bitmap_bin);
   return;
}

void StoryboardFactory::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   this->model_bin = model_bin;
   page_factory.set_model_bin(model_bin);
   return;
}

AllegroFlare::Screens::Storyboard* StoryboardFactory::create_images_storyboard_screen(std::vector<ALLEGRO_BITMAP*> source_bitmaps, int button_font_size)
{
   AllegroFlare::Screens::Storyboard* result;
   result = new AllegroFlare::Screens::Storyboard(event_emitter, font_bin);
   result->set_auto_advance(true);
   result->initialize();

   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages;
   for (auto &source_bitmap : source_bitmaps)
   {
      pages.push_back(new AllegroFlare::Elements::StoryboardPages::Image(source_bitmap));
   };

   AllegroFlare::Elements::Storyboard &storyboard_element = result->get_storyboard_element_ref();
   storyboard_element.set_button_font_size(button_font_size);
   storyboard_element.set_pages(pages);

   return result;
}

AllegroFlare::Screens::Storyboard* StoryboardFactory::create_advancing_text_storyboard_screen(std::vector<std::string> pages_text, int button_font_size, float page_top_padding, float page_left_padding, float page_right_padding, int page_text_font_size, std::string page_text_font_name, float page_text_line_height_multiplier)
{
   AllegroFlare::Screens::Storyboard* result;

   // create the storyboard container
   result = new AllegroFlare::Screens::Storyboard(event_emitter, font_bin);
   result->initialize();

   // tweak the button styling
   AllegroFlare::Elements::Storyboard &storyboard_element = result->get_storyboard_element_ref();
   storyboard_element.set_button_font_size(button_font_size);

   // create all the pages
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages;
   for (auto &page_text : pages_text)
   {
      AllegroFlare::Elements::StoryboardPages::AdvancingText* advancing_text_page =
         page_factory.create_advancing_text_page(page_text);
      advancing_text_page->set_top_padding(page_top_padding);
      advancing_text_page->set_left_padding(page_left_padding);
      advancing_text_page->set_right_padding(page_right_padding);
      advancing_text_page->set_font_name(page_text_font_name);
      advancing_text_page->set_font_size(page_text_font_size);
      advancing_text_page->set_line_height_multiplier(page_text_line_height_multiplier);
      pages.push_back(advancing_text_page);
   }
   storyboard_element.set_pages(pages);

   // return the result
   return result;
}


} // namespace AllegroFlare


