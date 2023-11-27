

#include <AllegroFlare/WorldMaps/Maps/Base.hpp>




namespace AllegroFlare
{
namespace WorldMaps
{
namespace Maps
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


std::string Base::location_id_at(float x, float y)
{
   return "";
}


} // namespace Maps
} // namespace WorldMaps
} // namespace AllegroFlare


