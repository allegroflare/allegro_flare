

#include <AllegroFlare/GameplayMechanics/Triggers/Basic.hpp>




namespace AllegroFlare
{
namespace GameplayMechanics
{
namespace Triggers
{


Basic::Basic()
   : AllegroFlare::GameplayMechanics::Triggers::Base(AllegroFlare::GameplayMechanics::Triggers::Basic::TYPE)
{
}


Basic::~Basic()
{
}


void Basic::on_trigger()
{
   // Nothing here
   return;
}


} // namespace Triggers
} // namespace GameplayMechanics
} // namespace AllegroFlare


