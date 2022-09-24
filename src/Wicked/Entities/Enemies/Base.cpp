

#include <Wicked/Entities/Enemies/Base.hpp>




namespace Wicked
{
namespace Entities
{
namespace Enemies
{


Base::Base()
   : Wicked::Entities::Basic2D()
   , movement_strategy(nullptr)
{
}


Base::~Base()
{
}


void Base::set_movement_strategy(Wicked::Entities::MovementStrategies2D::Base* movement_strategy)
{
   this->movement_strategy = movement_strategy;
}


Wicked::Entities::MovementStrategies2D::Base* Base::get_movement_strategy() const
{
   return movement_strategy;
}


void Base::update()
{
   if (movement_strategy)
   {
      movement_strategy->update();
   }
   return;
}

void Base::draw()
{
   Wicked::Entities::Basic2D::draw();
   return;
}


} // namespace Enemies
} // namespace Entities
} // namespace Wicked


