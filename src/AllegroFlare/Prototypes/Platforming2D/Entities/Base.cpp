

#include <AllegroFlare/Prototypes/Platforming2D/Entities/Base.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{
namespace Entities
{


Base::Base(std::string type, AllegroFlare::ElementID* parent)
   : AllegroFlare::ElementID(parent)
   , type(type)
   , parent(parent)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


AllegroFlare::ElementID* Base::get_parent() const
{
   return parent;
}


void Base::update()
{
   return;
}

void Base::draw()
{
   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


