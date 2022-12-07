

#include <AllegroFlare/Prototypes/Platforming2D/Entities/Enemies/Base.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{
namespace Entities
{
namespace Enemies
{


Base::Base()
   : AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D()
   , movement_strategy(nullptr)
{
}


Base::~Base()
{
}


void Base::set_movement_strategy(AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base* movement_strategy)
{
   this->movement_strategy = movement_strategy;
}


AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base* Base::get_movement_strategy() const
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
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::draw();
   return;
}


} // namespace Enemies
} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


