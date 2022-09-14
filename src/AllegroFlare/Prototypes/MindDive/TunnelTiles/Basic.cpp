

#include <AllegroFlare/Prototypes/MindDive/TunnelTiles/Basic.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace MindDive
{
namespace TunnelTiles
{


Basic::Basic(std::string property)
   : AllegroFlare::Prototypes::MindDive::TunnelTiles::Base(AllegroFlare::Prototypes::MindDive::TunnelTiles::Basic::TYPE)
   , property(property)
{
}


Basic::~Basic()
{
}


std::string Basic::get_property() const
{
   return property;
}




} // namespace TunnelTiles
} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


