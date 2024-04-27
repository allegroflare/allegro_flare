

#include <AllegroFlare/Prototypes/Platforming2D/Entities/BossZone.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{
namespace Entities
{


BossZone::BossZone()
   : AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D()
   , boss(nullptr)
{
}


BossZone::~BossZone()
{
}


void BossZone::set_boss(AllegroFlare::Prototypes::Platforming2D::Entities::Boss* boss)
{
   this->boss = boss;
}


AllegroFlare::Prototypes::Platforming2D::Entities::Boss* BossZone::get_boss() const
{
   return boss;
}




} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


