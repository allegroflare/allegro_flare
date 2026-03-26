

#include <AllegroFlare/Levels/Base.hpp>

#include <AllegroFlare/Logger.hpp>


namespace AllegroFlare
{
namespace Levels
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


void Base::load()
{
   AllegroFlare::Logger::throw_error(
      THIS_CLASS_AND_METHOD_NAME,
      "This method must be overridden in the derived class."
   );
   return;
}

void Base::unload()
{
   AllegroFlare::Logger::throw_error(
      THIS_CLASS_AND_METHOD_NAME,
      "This method must be overridden in the derived class."
   );
   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace Levels
} // namespace AllegroFlare


