

#include <AllegroFlare/Elements/DialogBoxFactory.hpp>

#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/Elements/DialogBoxes/ChapterTitle.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Wait.hpp>
#include <AllegroFlare/Elements/DialogBoxes/YouGotEvidence.hpp>
#include <allegro5/allegro.h>
#include <iostream>
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
      error_message << "[DialogBoxFactory::build_basic_test_dialog]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogBoxFactory::build_basic_test_dialog: error: guard \"al_is_system_installed()\" not met");
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
      error_message << "[DialogBoxFactory::create_basic_test_dialog]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogBoxFactory::create_basic_test_dialog: error: guard \"al_is_system_installed()\" not met");
   }
   AllegroFlare::Elements::DialogBoxes::Basic *basic_dialog_box = new AllegroFlare::Elements::DialogBoxes::Basic;
   basic_dialog_box->set_pages({
      { "Interesting.  I'm just sitting here working." },
      { "Oh well. I guess I'll just have to keep grinding." },
      { "At least I'm listening to some cool music." },
   });

   return basic_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::Basic DialogBoxFactory::build_basic_dialog(std::string speaking_character, std::vector<std::string> pages)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[DialogBoxFactory::build_basic_dialog]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogBoxFactory::build_basic_dialog: error: guard \"al_is_system_installed()\" not met");
   }
   AllegroFlare::Elements::DialogBoxes::Basic basic_dialog_box;
   // TODO: Trim speaking character first before checking if empty
   if (!speaking_character.empty())
   {
      basic_dialog_box.set_speaking_character(speaking_character);
   }
   basic_dialog_box.set_pages(pages);
   basic_dialog_box.set_created_at(al_get_time());
   return basic_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::Basic* DialogBoxFactory::create_basic_dialog(std::string speaking_character, std::vector<std::string> pages)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[DialogBoxFactory::create_basic_dialog]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogBoxFactory::create_basic_dialog: error: guard \"al_is_system_installed()\" not met");
   }
   AllegroFlare::Elements::DialogBoxes::Basic* basic_dialog_box = new AllegroFlare::Elements::DialogBoxes::Basic();
   // TODO: Trim speaking character first before checking if empty
   if (!speaking_character.empty())
   {
      basic_dialog_box->set_speaking_character(speaking_character);
   }
   basic_dialog_box->set_pages(pages);
   basic_dialog_box->set_created_at(al_get_time());
   return basic_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::Choice* DialogBoxFactory::create_choice_dialog(std::string speaking_character, std::string prompt, std::vector<std::pair<std::string, std::string>> options)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[DialogBoxFactory::create_choice_dialog]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogBoxFactory::create_choice_dialog: error: guard \"al_is_system_installed()\" not met");
   }
   AllegroFlare::Elements::DialogBoxes::Choice* choice_dialog_box
      = new AllegroFlare::Elements::DialogBoxes::Choice(prompt, options);
   // TODO: Trim speaking character first before checking if empty
   if (!speaking_character.empty())
   {
      choice_dialog_box->set_speaking_character(speaking_character);
   }
   choice_dialog_box->set_created_at(al_get_time());
   choice_dialog_box->initialize();

   return choice_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::YouGotAnItem* DialogBoxFactory::create_you_got_an_item_dialog(std::string item_name, std::string item_bitmap_identifier)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[DialogBoxFactory::create_you_got_an_item_dialog]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogBoxFactory::create_you_got_an_item_dialog: error: guard \"al_is_system_installed()\" not met");
   }
   AllegroFlare::Elements::DialogBoxes::YouGotAnItem* you_got_an_item_dialog_box =
      new AllegroFlare::Elements::DialogBoxes::YouGotAnItem(item_name, item_bitmap_identifier);
   you_got_an_item_dialog_box->set_created_at(al_get_time());

   return you_got_an_item_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::YouGotEvidence* DialogBoxFactory::create_you_got_new_evidence_dialog(std::string evidence_name, std::string evidence_bitmap_identifier)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[DialogBoxFactory::create_you_got_new_evidence_dialog]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogBoxFactory::create_you_got_new_evidence_dialog: error: guard \"al_is_system_installed()\" not met");
   }
   AllegroFlare::Elements::DialogBoxes::YouGotEvidence* you_got_new_evidence_dialog_box =
      new AllegroFlare::Elements::DialogBoxes::YouGotEvidence(evidence_name, evidence_bitmap_identifier);
   you_got_new_evidence_dialog_box->set_created_at(al_get_time());

   return you_got_new_evidence_dialog_box;
}

AllegroFlare::Elements::DialogBoxes::ChapterTitle* DialogBoxFactory::create_chapter_title_dialog(std::string title_text, float duration_seconds)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[DialogBoxFactory::create_chapter_title_dialog]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogBoxFactory::create_chapter_title_dialog: error: guard \"al_is_system_installed()\" not met");
   }
   // TODO: Use a DEFAULT_DURATION_SECIONDS from ChapterTitle
   AllegroFlare::Elements::DialogBoxes::ChapterTitle* chapter_title=
      new AllegroFlare::Elements::DialogBoxes::ChapterTitle();
   chapter_title->set_created_at(al_get_time());
   chapter_title->set_title_text(title_text);
   chapter_title->set_duration(duration_seconds);

   return chapter_title;
}

AllegroFlare::Elements::DialogBoxes::Wait* DialogBoxFactory::create_wait_dialog(float duration_seconds)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[DialogBoxFactory::create_wait_dialog]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DialogBoxFactory::create_wait_dialog: error: guard \"al_is_system_installed()\" not met");
   }
   AllegroFlare::Elements::DialogBoxes::Wait* you_got_new_evidence_dialog_box =
      new AllegroFlare::Elements::DialogBoxes::Wait(duration_seconds);
   you_got_new_evidence_dialog_box->set_created_at(al_get_time());
   you_got_new_evidence_dialog_box->initialize();

   return you_got_new_evidence_dialog_box;
}


} // namespace Elements
} // namespace AllegroFlare


