

#include <AllegroFlare/GameProgressAndStateInfos/Base.hpp>

#include <AllegroFlare/Logger.hpp>


namespace AllegroFlare
{
namespace GameProgressAndStateInfos
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


std::string Base::export_to_string()
{
   AllegroFlare::Logger::throw_error(
         "AllegroFlare::GameProgressAndStateInfos::Base::export_to_string",
         "not implemented"
      );
   return "";
}

void Base::import_from_string(std::string data_string)
{
   AllegroFlare::Logger::throw_error(
         "AllegroFlare::GameProgressAndStateInfos::Base::import_from_string",
         "not implemented"
      );
   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace GameProgressAndStateInfos
} // namespace AllegroFlare


