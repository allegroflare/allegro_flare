

#include <AllegroFlare/GameConfigurations/Base.hpp>

#include <AllegroFlare/Logger.hpp>


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


AllegroFlare::Levels::Base* Base::load_level_by_identifier(std::string level_identifier)
{
   // TODO: Add tests for this method or consider making it a pure virtual
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::load_level_by_identifier"
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return nullptr;
}

std::vector<std::pair<std::string, std::string>> Base::build_level_list_for_level_select_screen_by_identifier(std::string identifier)
{
   // TODO: Add tests for this method or consider making it a pure virtual
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::build_level_list_for_level_select_screen_by_identifier"
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return {};
}

AllegroFlare::DialogTree::NodeBank Base::build_dialog_bank_by_identifier(std::string identifier)
{
   // TODO: Add tests for this method or consider making it a pure virtual
   AllegroFlare::DialogTree::NodeBank node_bank;
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::build_dialog_bank_by_identifier",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return node_bank;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace GameConfigurations
} // namespace AllegroFlare


