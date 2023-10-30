

#include <AllegroFlare/GameConfigurations/Base.hpp>




namespace AllegroFlare
{
namespace GameConfigurations
{


Base::Base(std::string type)
   : type(type)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


void* Base::load_level_by_identifier(std::string level_identifier)
{
   // TODO: Replace void* with a class of some kind representing a level (AllegroFlare::Levels::Base* probably)
   throw std::runtime_error("LevelFactories/Base Not implemented in base class");
   return nullptr;
}

std::vector<std::pair<std::string, std::string>> Base::build_level_list_for_level_select_screen_by_identifier(std::string identifier)
{
   throw std::runtime_error(
         "LevelFactories/Base build_level_list_for_level_select_screen_by_identifier Not implemented in base class"
      );
   return {};
}

AllegroFlare::DialogTree::NodeBank Base::build_dialog_bank_by_identifier(std::string identifier)
{
   AllegroFlare::DialogTree::NodeBank node_bank;
   throw std::runtime_error(
         "LevelFactories/Base build_dialog_bank_by_identifier Not implemented in base class"
      );
   return node_bank;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace GameConfigurations
} // namespace AllegroFlare


