

#include <AllegroFlare/Tiled/TMJGroup.hpp>




namespace AllegroFlare
{
namespace Tiled
{


TMJGroup::TMJGroup(int id, std::string name, float offset_x, float offset_y)
   : id(id)
   , name(name)
   , offset_x(offset_x)
   , offset_y(offset_y)
{
}


TMJGroup::~TMJGroup()
{
}




} // namespace Tiled
} // namespace AllegroFlare


