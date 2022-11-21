

#include <AllegroFlare/Elements/DialogBoxFactory.hpp>

#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <allegro5/allegro.h>
#include <sstream>
#include <stdexcept>


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
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "DialogBoxFactory" << "::" << "build_basic_test_dialog" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
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
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "DialogBoxFactory" << "::" << "create_basic_test_dialog" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
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
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "DialogBoxFactory" << "::" << "build_basic_dialog" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Elements::DialogBoxes::Basic basic_dialog_box;
   basic_dialog_box.set_pages(pages);
   basic_dialog_box.set_created_at(al_get_time());
   return basic_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::Basic* DialogBoxFactory::create_basic_dialog(std::vector<std::string> pages)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "DialogBoxFactory" << "::" << "create_basic_dialog" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Elements::DialogBoxes::Basic* basic_dialog_box = new AllegroFlare::Elements::DialogBoxes::Basic();
   basic_dialog_box->set_pages(pages);
   basic_dialog_box->set_created_at(al_get_time());
   return basic_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::Choice* DialogBoxFactory::create_choice_dialog(std::string prompt, std::vector<std::pair<std::string, std::string>> options)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "DialogBoxFactory" << "::" << "create_choice_dialog" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Elements::DialogBoxes::Choice* choice_dialog_box
      = new AllegroFlare::Elements::DialogBoxes::Choice(prompt, options);
   choice_dialog_box->set_created_at(al_get_time());
   choice_dialog_box->initialize();

   return choice_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::YouGotAnItem* DialogBoxFactory::create_you_got_an_item_dialog(std::string item_name, std::string item_bitmap_identifier)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "DialogBoxFactory" << "::" << "create_you_got_an_item_dialog" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Elements::DialogBoxes::YouGotAnItem* you_got_an_item_dialog_box =
      new AllegroFlare::Elements::DialogBoxes::YouGotAnItem(item_name, item_bitmap_identifier);
   you_got_an_item_dialog_box->set_created_at(al_get_time());

   return you_got_an_item_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::YouGotAnItem* DialogBoxFactory::create_you_got_new_evidence_dialog(std::string evidence_name, std::string evidence_bitmap_identifier)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "DialogBoxFactory" << "::" << "create_you_got_new_evidence_dialog" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Elements::DialogBoxes::YouGotAnItem* you_got_new_evidence_dialog_box =
      new AllegroFlare::Elements::DialogBoxes::YouGotAnItem(evidence_name, evidence_bitmap_identifier);
   you_got_new_evidence_dialog_box->set_created_at(al_get_time());

   return you_got_new_evidence_dialog_box;
}


} // namespace Elements
} // namespace AllegroFlare


