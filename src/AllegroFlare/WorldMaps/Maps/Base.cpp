

#include <AllegroFlare/WorldMaps/Maps/Base.hpp>

#include <AllegroFlare/Logger.hpp>


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
   AllegroFlare::Logger::throw_unimplemented_for_base_class_error(
      "AllegroFlare::WorldMaps::Maps::Base::location_id_at"
   );
   return "";
}


} // namespace Maps
} // namespace WorldMaps
} // namespace AllegroFlare


