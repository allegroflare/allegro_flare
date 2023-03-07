

#include <AllegroFlare/PhysicalInputDevices/Base.hpp>




namespace AllegroFlare
{
namespace PhysicalInputDevices
{


Base::Base(std::string type, std::string name)
   : type(type)
   , name(name)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


std::string Base::get_name() const
{
   return name;
}


bool Base::is_keyboard()
{
   return false;
}

bool Base::is_joystick()
{
   return false;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace PhysicalInputDevices
} // namespace AllegroFlare


