

#include <AllegroFlare/Prototypes/Platforming2D/Entities/Boss.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{
namespace Entities
{


Boss::Boss()
   : AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D()
   , health(16.0f)
   , max_health(16.0f)
{
}


Boss::~Boss()
{
}


void Boss::set_health(float health)
{
   this->health = health;
}


void Boss::set_max_health(float max_health)
{
   this->max_health = max_health;
}


float Boss::get_health() const
{
   return health;
}


float Boss::get_max_health() const
{
   return max_health;
}




} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


