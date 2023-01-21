

#include <AllegroFlare/RenderSurfaces/Base.hpp>




namespace AllegroFlare
{
namespace RenderSurfaces
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






float Base::get_center()
{
   return get_width() * 0.5f;
}

float Base::get_middle()
{
   return get_height() * 0.5f;
}


} // namespace RenderSurfaces
} // namespace AllegroFlare


