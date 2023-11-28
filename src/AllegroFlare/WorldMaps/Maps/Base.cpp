

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


std::pair<float, float> Base::infer_primary_point_of_interest_coordinates()
{
   AllegroFlare::Logger::throw_unimplemented_for_base_class_error(
      "AllegroFlare::WorldMaps::Maps::Base::infer_primary_point_of_interest"
   );
   return { 0.0f, 0.0f };
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


