

#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>



namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


Base::Base(std::string type)
   : type(type)
   , created_at(0)
{
}


Base::~Base()
{
}


void Base::set_created_at(float created_at)
{
   this->created_at = created_at;
}


std::string Base::get_type()
{
   return type;
}


float Base::get_created_at()
{
   return created_at;
}


void Base::update()
{
   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}
} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


