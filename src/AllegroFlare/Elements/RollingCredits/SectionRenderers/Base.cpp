

#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Base.hpp>



namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{
namespace SectionRenderers
{


Base::Base(std::string type)
   : type(type)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


float Base::render(bool only_calculate_height_dont_render)
{
   return 0.0f;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}
} // namespace SectionRenderers
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


