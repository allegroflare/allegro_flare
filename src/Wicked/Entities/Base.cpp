

#include <Wicked/Entities/Base.hpp>




namespace Wicked
{
namespace Entities
{


Base::Base(AllegroFlare::ElementID* parent)
   : AllegroFlare::ElementID(parent)
   , parent(parent)
{
}


Base::~Base()
{
}


void Base::update()
{
   return;
}

void Base::draw()
{
   return;
}


} // namespace Entities
} // namespace Wicked


