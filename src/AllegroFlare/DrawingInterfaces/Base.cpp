


#include <AllegroFlare/DrawingInterfaces/Base.hpp>



namespace AllegroFlare
{
namespace DrawingInterfaces
{



Base::Base(std::string drawing_mode_name)
   : drawing_mode_name(drawing_mode_name)
{}




Base::~Base()
{}




std::string Base::get_mode_name()
{
   return drawing_mode_name;
}



} // namespace DrawingInterfaces
} // namespace AllegroFlare



