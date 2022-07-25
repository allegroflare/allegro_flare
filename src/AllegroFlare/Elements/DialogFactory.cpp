

#include <AllegroFlare/Elements/DialogFactory.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
namespace Elements
{


DialogFactory::DialogFactory()
{
}


DialogFactory::~DialogFactory()
{
}


AllegroFlare::Elements::DialogBoxes::Basic DialogFactory::build_basic_test_dialog()
{
   AllegroFlare::Elements::DialogBoxes::Basic basic_dialog_box;
   basic_dialog_box.set_pages({
      { "Interesting.  I'm just sitting here working." },
      { "Oh well. I guess I'll just have to keep grinding." },
      { "At least I'm listening to some cool music." },
   });

   return basic_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::Basic* DialogFactory::create_basic_test_dialog()
{
   AllegroFlare::Elements::DialogBoxes::Basic *basic_dialog_box = new AllegroFlare::Elements::DialogBoxes::Basic;
   basic_dialog_box->set_pages({
      { "Interesting.  I'm just sitting here working." },
      { "Oh well. I guess I'll just have to keep grinding." },
      { "At least I'm listening to some cool music." },
   });

   return basic_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::Basic DialogFactory::build_basic_dialog(std::vector<std::string> pages)
{
   AllegroFlare::Elements::DialogBoxes::Basic basic_dialog_box;
   basic_dialog_box.set_pages(pages);
   return basic_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::Basic* DialogFactory::create_basic_dialog(std::vector<std::string> pages)
{
   AllegroFlare::Elements::DialogBoxes::Basic* basic_dialog_box = new AllegroFlare::Elements::DialogBoxes::Basic();
   basic_dialog_box->set_pages(pages);
   return basic_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::TitleText* DialogFactory::create_title_text_dialog(std::string title_text)
{
   AllegroFlare::Elements::DialogBoxes::TitleText* title_text_dialog_box = new AllegroFlare::Elements::DialogBoxes::TitleText(title_text);
   return title_text_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::Choice* DialogFactory::create_choice_dialog(std::string prompt, std::vector<std::pair<std::string, std::string>> options)
{
   AllegroFlare::Elements::DialogBoxes::Choice* choice_dialog_box = new AllegroFlare::Elements::DialogBoxes::Choice(prompt, options);
   choice_dialog_box->initialize();
   //basic_dialog_box->set_pages(pages); // ??? hmm
   return choice_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::YouGotAnItem* DialogFactory::create_you_got_an_item_dialog(int item_num, std::string item_name, std::string item_bitmap_identifier)
{
   AllegroFlare::Elements::DialogBoxes::YouGotAnItem* you_got_an_item_dialog_box =
   new AllegroFlare::Elements::DialogBoxes::YouGotAnItem(item_num, item_name, item_bitmap_identifier);
   you_got_an_item_dialog_box->set_created_at(al_get_time());
   you_got_an_item_dialog_box->show();
   //choice_dialog_box->initialize(); // doesn't seem to require initialization
   return you_got_an_item_dialog_box;
}
} // namespace Elements
} // namespace AllegroFlare


