

#include <AllegroFlare/Elements/DialogBoxFactory.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
namespace Elements
{


DialogBoxFactory::DialogBoxFactory()
{
}


DialogBoxFactory::~DialogBoxFactory()
{
}


AllegroFlare::Elements::DialogBoxes::Basic DialogBoxFactory::build_basic_test_dialog()
{
   AllegroFlare::Elements::DialogBoxes::Basic basic_dialog_box;
   basic_dialog_box.set_pages({
      { "Interesting.  I'm just sitting here working." },
      { "Oh well. I guess I'll just have to keep grinding." },
      { "At least I'm listening to some cool music." },
   });

   return basic_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::Basic* DialogBoxFactory::create_basic_test_dialog()
{
   AllegroFlare::Elements::DialogBoxes::Basic *basic_dialog_box = new AllegroFlare::Elements::DialogBoxes::Basic;
   basic_dialog_box->set_pages({
      { "Interesting.  I'm just sitting here working." },
      { "Oh well. I guess I'll just have to keep grinding." },
      { "At least I'm listening to some cool music." },
   });

   return basic_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::Basic DialogBoxFactory::build_basic_dialog(std::vector<std::string> pages)
{
   AllegroFlare::Elements::DialogBoxes::Basic basic_dialog_box;
   basic_dialog_box.set_pages(pages);
   return basic_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::Basic* DialogBoxFactory::create_basic_dialog(std::vector<std::string> pages)
{
   AllegroFlare::Elements::DialogBoxes::Basic* basic_dialog_box = new AllegroFlare::Elements::DialogBoxes::Basic();
   basic_dialog_box->set_pages(pages);
   return basic_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::Choice* DialogBoxFactory::create_choice_dialog(std::string prompt, std::vector<std::pair<std::string, std::string>> options)
{
   AllegroFlare::Elements::DialogBoxes::Choice* choice_dialog_box
      = new AllegroFlare::Elements::DialogBoxes::Choice(prompt, options);
   choice_dialog_box->initialize();
   //basic_dialog_box->set_pages(pages); // ??? hmm
   return choice_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::YouGotAnItem* DialogBoxFactory::create_you_got_an_item_dialog(std::string item_name, std::string item_bitmap_identifier)
{
   AllegroFlare::Elements::DialogBoxes::YouGotAnItem* you_got_an_item_dialog_box =
      new AllegroFlare::Elements::DialogBoxes::YouGotAnItem(item_name, item_bitmap_identifier);
   you_got_an_item_dialog_box->set_created_at(al_get_time());
   you_got_an_item_dialog_box->show();
   //choice_dialog_box->initialize(); // doesn't seem to require initialization
   return you_got_an_item_dialog_box;
}
} // namespace Elements
} // namespace AllegroFlare


