

#include <AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>



namespace AllegroFlare
{
namespace MotionComposer
{
namespace Messages
{


AddActor2D::AddActor2D(std::string property)
   : AllegroFlare::MotionComposer::Messages::Base("AddActor2D")
   , property(property)
{
}


AddActor2D::~AddActor2D()
{
}


std::string AddActor2D::get_property()
{
   return property;
}


} // namespace Messages
} // namespace MotionComposer
} // namespace AllegroFlare


