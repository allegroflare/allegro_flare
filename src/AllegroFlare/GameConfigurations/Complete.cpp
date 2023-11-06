

#include <AllegroFlare/GameConfigurations/Complete.hpp>

#include <AllegroFlare/Achievement.hpp>
#include <AllegroFlare/Logger.hpp>


namespace AllegroFlare
{
namespace GameConfigurations
{


Complete::Complete(std::string type)
   : type(type)
{
}


Complete::~Complete()
{
}


std::string Complete::get_type() const
{
   return type;
}


AllegroFlare::Levels::Base* Complete::load_level_by_identifier(std::string level_identifier)
{
   // TODO: Add tests for this method or consider making it a pure virtual
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::load_level_by_identifier"
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return nullptr;
}

std::vector<std::pair<std::string, std::string>> Complete::build_level_list_for_level_select_screen_by_identifier(std::string identifier)
{
   // TODO: Add tests for this method or consider making it a pure virtual
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::build_level_list_for_level_select_screen_by_identifier"
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return {};
}

AllegroFlare::DialogTree::NodeBank Complete::build_dialog_bank_by_identifier(std::string identifier)
{
   // TODO: Add tests for this method or consider making it a pure virtual
   AllegroFlare::DialogTree::NodeBank node_bank;
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::build_dialog_bank_by_identifier",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return node_bank;
}

std::vector<std::tuple<std::string, AllegroFlare::Achievement*, bool, bool>> Complete::build_achievements()
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::build_achievements",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return {};
}

std::vector<AllegroFlare::Elements::StoryboardPages::Base *> Complete::create_intro_logos_storyboard_pages()
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::create_intro_logos_storyboard_pagse",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   //AllegroFlare::StoryboardPageFactory page_factory;
   //page_factory.set_font_bin(font_bin);
   //page_factory.set_bitmap_bin(bitmap_bin);
   //page_factory.set_model_bin(model_bin);

   //std::vector<AllegroFlare::Elements::StoryboardPages::Base *> result =
   //{
      //page_factory.create_image_with_advancing_text_page(
         //"storyboard-1-01-1165x500.png",
         //"Once upon a time, in a magical kingdom ruled by a wise and just queen, a young hero sets out on a "
            //"journey to prove himself and save his people from a terrible curse."
      //),
      //page_factory.create_image_with_advancing_text_page(
         //"storyboard-2-01-1165x500.png",
         //"With the help of his trusty sidekick and a band of unlikely allies, he must navigate treacherous "
            //"terrain and battle fierce foes."
      //),
      //page_factory.create_advancing_text_page(
        //"And achieve his goal to save the kingdom."
      //),
   //};
   return {};
}

bool Complete::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace GameConfigurations
} // namespace AllegroFlare


