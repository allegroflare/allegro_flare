

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
   , boss_is_defeated(false)
{
}


BossZone::~BossZone()
{
}


void BossZone::set_boss(AllegroFlare::Prototypes::Platforming2D::Entities::Boss* boss)
{
   this->boss = boss;
}


void BossZone::set_boss_is_defeated(bool boss_is_defeated)
{
   this->boss_is_defeated = boss_is_defeated;
}


AllegroFlare::Prototypes::Platforming2D::Entities::Boss* BossZone::get_boss() const
{
   return boss;
}


bool BossZone::get_boss_is_defeated() const
{
   return boss_is_defeated;
}




} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


