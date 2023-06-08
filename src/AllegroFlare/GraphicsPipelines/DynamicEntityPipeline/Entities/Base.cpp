

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Base.hpp>




namespace AllegroFlare
{
namespace GraphicsPipelines
{
namespace DynamicEntityPipeline
{
namespace Entities
{


Base::Base(std::string type)
   : AllegroFlare::ElementID()
   , type(type)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace Entities
} // namespace DynamicEntityPipeline
} // namespace GraphicsPipelines
} // namespace AllegroFlare


