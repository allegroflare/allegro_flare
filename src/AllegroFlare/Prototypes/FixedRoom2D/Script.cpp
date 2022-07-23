

#include <AllegroFlare/Prototypes/FixedRoom2D/Script.hpp>



namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


Script::Script(std::vector<std::string> lines)
   : lines(lines)
{
}


Script::~Script()
{
}


void Script::set_lines(std::vector<std::string> lines)
{
   this->lines = lines;
}


std::vector<std::string> Script::get_lines()
{
   return lines;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


