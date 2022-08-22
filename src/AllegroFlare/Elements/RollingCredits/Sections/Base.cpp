

#include <AllegroFlare/Elements/RollingCredits/Sections/Base.hpp>



namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{
namespace Sections
{


Base::Base(std::string type)
   : type(type)
{
}


Base::~Base()
{
}


std::string Base::get_type()
{
   return type;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}
} // namespace Sections
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


