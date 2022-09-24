

#include <AllegroFlare/Shaders/Base.hpp>




namespace AllegroFlare
{
namespace Shaders
{


Base::Base(std::string type, std::string vertex_source_code, std::string fragment_source_code)
   : AllegroFlare::Shader(vertex_source_code, fragment_source_code)
   , type(type)
   , vertex_source_code(vertex_source_code)
   , fragment_source_code(fragment_source_code)
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


} // namespace Shaders
} // namespace AllegroFlare


