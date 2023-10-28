

#include <AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver.hpp>

#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/BasicCentered.hpp>
#include <AllegroFlare/DialogSystem/Characters/Basic.hpp>
#include <AllegroFlare/DialogSystem/NodeStates/Wait.hpp>
#include <AllegroFlare/DialogTree/Nodes/ChapterTitle.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitProgram.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/DialogTree/Nodes/Wait.hpp>
#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogSystemDrivers
{


BasicCharacterDialogDriver::BasicCharacterDialogDriver(AllegroFlare::BitmapBin* bitmap_bin)
   : AllegroFlare::DialogSystemDrivers::Base(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE)
   , bitmap_bin(bitmap_bin)
   , dialog_roll()
   , initialized(false)
   , active_character_staging_layout(nullptr)
   , character_roster(nullptr)
   , scene_index(nullptr)
   , chapter_index(nullptr)
{
}


BasicCharacterDialogDriver::~BasicCharacterDialogDriver()
{
}


void BasicCharacterDialogDriver::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void BasicCharacterDialogDriver::set_dialog_roll(AllegroFlare::Elements::DialogRoll dialog_roll)
{
   this->dialog_roll = dialog_roll;
}


AllegroFlare::Elements::DialogRoll BasicCharacterDialogDriver::get_dialog_roll() const
{
   return dialog_roll;
}


AllegroFlare::Elements::DialogRoll &BasicCharacterDialogDriver::get_dialog_roll_ref()
{
   return dialog_roll;
}


void BasicCharacterDialogDriver::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::initialize: error: guard \"(!initialized)\" not met");
   }
   active_character_staging_layout = new AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered();
   initialized = true;
   return;
}

void BasicCharacterDialogDriver::destroy()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::destroy]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::destroy: error: guard \"initialized\" not met");
   }
   // TODO: consider where delete character_roster, scene_index should occour
   delete active_character_staging_layout;
   return;
}

void BasicCharacterDialogDriver::on_switch_in()
{
   if (active_character_staging_layout) active_character_staging_layout->show();
   return;
}

void BasicCharacterDialogDriver::on_deactivate()
{
   if (active_character_staging_layout) active_character_staging_layout->hide();
   return;
}

void BasicCharacterDialogDriver::on_render()
{
   if (active_character_staging_layout) active_character_staging_layout->render();
   return;
}

void BasicCharacterDialogDriver::clear_character_staging_layout()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::clear_character_staging_layout]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::clear_character_staging_layout: error: guard \"initialized\" not met");
   }
   if (active_character_staging_layout->is_type(
            AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered::TYPE
         ))
   {
      AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered *as =
         static_cast<AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered*>(
            active_character_staging_layout
         );
      as->clear_speaking_character_bitmap();
   }
   else
   {
      throw std::runtime_error(
         "DialogSystemDrivers::BasicCharacterDialogDriver::set_speaking_character: error: Unable to perform action because "
            "\"active_character_staging_layout\" is of type \"" + active_character_staging_layout->get_type() + "\" "
            "and a condition is not provided to handle this type."
      );
   }
   return;
}

bool BasicCharacterDialogDriver::activate_dialog_node_by_name(AllegroFlare::DialogSystem::DialogSystem* dialog_system, std::string active_dialog_node_name, AllegroFlare::DialogTree::Nodes::Base* active_dialog_node, void* user_data)
{
   // TODO: Remove this call  to _func and only call this containing method externally
   return __activate_dialog_node_by_name_func(dialog_system, active_dialog_node_name, active_dialog_node, user_data);
}

bool BasicCharacterDialogDriver::__activate_dialog_node_by_name_func(AllegroFlare::DialogSystem::DialogSystem* dialog_system, std::string active_dialog_node_name, AllegroFlare::DialogTree::Nodes::Base* active_dialog_node, void* user_data)
{
   if (!(dialog_system))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::__activate_dialog_node_by_name_func]: error: guard \"dialog_system\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::__activate_dialog_node_by_name_func: error: guard \"dialog_system\" not met");
   }
   if (!(active_dialog_node))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::__activate_dialog_node_by_name_func]: error: guard \"active_dialog_node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::__activate_dialog_node_by_name_func: error: guard \"active_dialog_node\" not met");
   }
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::__activate_dialog_node_by_name_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::__activate_dialog_node_by_name_func: error: guard \"initialized\" not met");
   }
   std::string &dialog_name = active_dialog_node_name;

   if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::MultipageWithOptions::TYPE))
   {
      AllegroFlare::DialogTree::Nodes::MultipageWithOptions *as_multipage_with_options =
         static_cast<AllegroFlare::DialogTree::Nodes::MultipageWithOptions*>(active_dialog_node);

      std::string node_pages_speaker = as_multipage_with_options->get_speaker();
      std::vector<std::string> node_pages = as_multipage_with_options->get_pages();
      std::vector<std::string> node_options_as_text = as_multipage_with_options->build_options_as_text();

      if (node_options_as_text.empty())
      {
         throw std::runtime_error(
            "DialogSystemDrivers::BasicCharacterDialogDriver::activate_dialog_node_by_name: error: Expecting 1 or many options for node named \""
               + dialog_name + "\" but there are no options."
         );
      }
      else if (node_options_as_text.size() == 1)
      {
         // If dialog has only one option, spawn a basic dialog
         set_speaking_character_avatar(node_pages_speaker);
         dialog_system->spawn_basic_dialog(node_pages_speaker, node_pages);
         //append_to_dialog_roll(node_pages_speaker, node_pages[0]); // TODO: join(node_pages);
      }
      else // (node_options_as_text.size() > 1)
      {
         // TODO: Here, if dialog has multiple options, spawn a "choice" dialog
         if (node_pages.size() != 1)
         {
            throw std::runtime_error(
               "DialogSystemDrivers::BasicCharacterDialogDriver::activate_dialog_node_by_name: error: Expecting only 1 page for dialog node \""
                  + dialog_name + "\" (because it is going to be used to build a Choice dialog, "
                  "but there are \"" + std::to_string(node_pages.size()) + "\" pages."
            );
         }
         set_speaking_character_avatar(node_pages_speaker);
         dialog_system->spawn_choice_dialog(node_pages_speaker, node_pages[0], node_options_as_text);
         //append_to_dialog_roll(node_pages_speaker, node_pages[0]); // TODO: join(node_pages);
      }
   }
   else if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::Wait::TYPE))
   {
      // Cast our class
      AllegroFlare::DialogTree::Nodes::Wait *as =
         static_cast<AllegroFlare::DialogTree::Nodes::Wait*>(active_dialog_node);

      // Create a new state for this node
      //AllegroFlare::DialogSystem::NodeStates::Wait *wait_node_state =
            //new AllegroFlare::DialogSystem::NodeStates::Wait(as);
      //wait_node_state->initialize();

      // Assign the state to our "active_dialog_node_state" so it can be managed
      float duration_seconds = as->get_duration_sec();
      dialog_system->spawn_wait_dialog(duration_seconds);
      //dialog_system->set_active_dialog_node_state(wait_node_state);
   }
   else if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::ChapterTitle::TYPE))
   {
      // Cast our class
      AllegroFlare::DialogTree::Nodes::ChapterTitle *as =
         static_cast<AllegroFlare::DialogTree::Nodes::ChapterTitle*>(active_dialog_node);

      // Create a new state for this node
      //AllegroFlare::DialogSystem::NodeStates::Wait *wait_node_state =
            //new AllegroFlare::DialogSystem::NodeStates::Wait(as);
      //wait_node_state->initialize();

      // Assign the state to our "active_dialog_node_state" so it can be managed
      //float duration_seconds = as->get_duration_sec();
      dialog_system->spawn_chapter_title_dialog(
            as->get_title_text(),
            as->get_duration()
         );
      //dialog_system->set_active_dialog_node_state(wait_node_state);
   }
   else if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::ExitDialog::TYPE))
   {
      //AllegroFlare::DialogTree::Nodes::ExitDialog *as =
         //static_cast<AllegroFlare::DialogTree::Nodes::ExitDialog*>(base);
      dialog_system->shutdown_dialog(); // TODO: See if this is a correct expectation for this event
   }
   /*
   else if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::EnterScene::TYPE))
   {
      // TODO: thrwo
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::activate_dialog_node_by_name_func",
         "Handling of \"AllegroFlare::DialogTree::Nodes::EnterScene::TYPE\" not implemented"
      );
      //AllegroFlare::DialogTree::Nodes::ExitDialog *as =
         //static_cast<AllegroFlare::DialogTree::Nodes::ExitDialog*>(base);
      //dialog_system->shutdown_dialog(); // TODO: See if this is a correct expectation for this event
   }
   */
   else if (active_dialog_node->is_type(AllegroFlare::DialogTree::Nodes::ExitProgram::TYPE))
   {
      // TODO: Test this event emission
      dialog_system->get_event_emitter()->emit_exit_game_event();
      // TODO: Exit program (either set shutdown_system on framework or emit event)
   }
   else
   {
      bool handled = false;
      if (get_activate_dialog_node_type_unhandled_func())
      {
         handled = get_activate_dialog_node_type_unhandled_func()(
               dialog_system,
               get_activate_dialog_node_type_unhandled_func_user_data()
         );
      }

      if (!handled)
      {
         throw std::runtime_error(
            "DialogSystemDrivers::BasicCharacterDialogDriver::activate_dialog_node_by_name: error: Unable to handle dialog node activation on type \""
               + active_dialog_node->get_type() + "\". A condition is not provided to handle this type."
         );
      }
   }
   return true;
}

void BasicCharacterDialogDriver::set_speaking_character_avatar(std::string speaking_character_identifier, std::string speaking_character_expression)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::set_speaking_character_avatar]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::set_speaking_character_avatar: error: guard \"initialized\" not met");
   }

   //guards: [ driver.active_character_staging_layout, (speaking_character_identifier.empty()) ]

   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver = this;

   //if (_driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   //{
      //AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
         //static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);

      //{
      if (driver->active_character_staging_layout->is_type(
               AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered::TYPE
            ))
      {
         AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered *as =
            static_cast<AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered*>(
               driver->active_character_staging_layout
            );
         ALLEGRO_BITMAP *speaking_character_bitmap = lookup_speaking_character_avatar(
               speaking_character_identifier,
               speaking_character_expression
            );
         if (!speaking_character_bitmap) as->clear_speaking_character_bitmap();
         else as->set_speaking_character_bitmap(speaking_character_bitmap);
         // TODO: Set the character
      }
      else
      {
         throw std::runtime_error(
            "DialogSystemSystemDrivers::BasicCharacterDialogDriver::set_speaking_character: error: Unable to perform action because "
               "\"driver.active_character_staging_layout\" is of type \"" + driver->active_character_staging_layout->get_type() + "\" "
               "and a condition is not provided to handle this type."
         );
      }
   //}
   return;
}

ALLEGRO_BITMAP* BasicCharacterDialogDriver::lookup_speaking_character_avatar(std::string speaking_character_identifier, std::string speaking_character_expression)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::lookup_speaking_character_avatar]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::lookup_speaking_character_avatar: error: guard \"initialized\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::lookup_speaking_character_avatar]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::lookup_speaking_character_avatar: error: guard \"bitmap_bin\" not met");
   }
   //if (!_driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   //{
      //throw std::runtime_error("Unknown _driver type");
   //}

    
   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver = this;


   //AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
      //static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);

   if (driver->character_roster)
   {
      if (!driver->character_roster->character_exists_by_name(speaking_character_identifier))
      {
         // Throw for now
         std::stringstream available_character_names;
         available_character_names << "[ ";
         for (auto &character_identifier : driver->character_roster->get_character_names())
         {
            available_character_names << "\"" << character_identifier << "\", ";
         }
         available_character_names << " ]";

         throw std::runtime_error("Roster is present, but character \"" + speaking_character_identifier + "\" "
                                  "does not exist in roster. Available names are " + available_character_names.str()
                                  );
      }

      AllegroFlare::DialogSystem::Characters::Base *base =
         driver->character_roster->find_character_by_name(speaking_character_identifier);

      if (base->is_type(AllegroFlare::DialogSystem::Characters::Basic::TYPE))
      {
         AllegroFlare::DialogSystem::Characters::Basic *as =
            static_cast<AllegroFlare::DialogSystem::Characters::Basic*>(base);

         std::string bitmap_identifier_to_use = "";
         if (as->expression_exists(speaking_character_expression))
         {
            bitmap_identifier_to_use = as->find_expression(speaking_character_expression);
         }
         else
         {
            // TODO: Add report about missing expression
            bitmap_identifier_to_use = as->get_avatar_portrait_identifier();
         }

         return bitmap_bin->auto_get(bitmap_identifier_to_use);
      }
      else
      {
         throw std::runtime_error("DialogSystemDrivers::BasicCharacterDialogDriver: unknown handled character type");
      }
   }
   return nullptr;
}

AllegroFlare::DialogSystem::Characters::Basic* BasicCharacterDialogDriver::find_character_by_identifier_as_Basic(std::string character_identifier)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::find_character_by_identifier_as_Basic]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::find_character_by_identifier_as_Basic: error: guard \"initialized\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::find_character_by_identifier_as_Basic]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::find_character_by_identifier_as_Basic: error: guard \"bitmap_bin\" not met");
   }
   //if (!_driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   //{
      //throw std::runtime_error("Unknown _driver type");
   //}

    
   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver = this;


   //AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
      //static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);

   if (!driver->character_roster)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver"
         "Expecting character_roster to not be a nullptr"
      );
   }

      if (!driver->character_roster->character_exists_by_name(character_identifier))
      {
         // Throw for now
         std::stringstream available_character_names;
         available_character_names << "[ ";
         for (auto &character_identifier : driver->character_roster->get_character_names())
         {
            available_character_names << "\"" << character_identifier << "\", ";
         }
         available_character_names << " ]";

         std::string error_message = "Roster is present, but character \"" + character_identifier + "\" "
                                  "does not exist in roster. Available names are " + available_character_names.str();

         AllegroFlare::Logger::throw_error(
            "AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver",
            error_message
         );
      }

      AllegroFlare::DialogSystem::Characters::Base *base =
         driver->character_roster->find_character_by_name(character_identifier);

      if (base->is_type(AllegroFlare::DialogSystem::Characters::Basic::TYPE))
      {
         AllegroFlare::DialogSystem::Characters::Basic *as =
            static_cast<AllegroFlare::DialogSystem::Characters::Basic*>(base);

         return as;

         //std::string bitmap_identifier_to_use = "";
         //if (as->expression_exists(speaking_character_expression))
         //{
            //bitmap_identifier_to_use = as->find_expression(speaking_character_expression);
         //}
         //else
         //{
            //// TODO: Add report about missing expression
            //bitmap_identifier_to_use = as->get_avatar_portrait_identifier();
         //}

         //return bitmap_bin->auto_get(bitmap_identifier_to_use);
      }
      else
      {
         throw std::runtime_error(
            "DialogSystemDrivers::BasicCharacterDialogDriver::lookup_speaking_character_as_Basic"
            "unknown handled character type"
         );
      }
   //}
   return nullptr;
}

void BasicCharacterDialogDriver::append_to_dialog_roll(std::string speaking_character, std::string dialog)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[BasicCharacterDialogDriver::append_to_dialog_roll]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicCharacterDialogDriver::append_to_dialog_roll: error: guard \"initialized\" not met");
   }
   dialog_roll.append_log(speaking_character, dialog);
   return;
}


} // namespace DialogSystemDrivers
} // namespace AllegroFlare


