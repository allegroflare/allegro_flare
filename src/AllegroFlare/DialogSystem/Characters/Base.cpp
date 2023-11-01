

#include <AllegroFlare/DialogSystem/Characters/Base.hpp>

#include <AllegroFlare/Logger.hpp>


namespace AllegroFlare
{
namespace DialogSystem
{
namespace Characters
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


std::string Base::get_display_name()
{
   // TODO: Consider moving this to pure_virtual
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::DialogSystem::Characters::Base::get_display_name",
      "Not implemented in base class"
   );
   return "";
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace Characters
} // namespace DialogSystem
} // namespace AllegroFlare


