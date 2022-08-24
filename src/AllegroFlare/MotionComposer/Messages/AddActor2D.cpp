

#include <AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>



namespace AllegroFlare
{
namespace MotionComposer
{
namespace Messages
{


AddActor2D::AddActor2D(std::string identifier)
   : AllegroFlare::MotionComposer::Messages::Base("AddActor2D")
   , identifier(identifier)
{
}


AddActor2D::~AddActor2D()
{
}


void AddActor2D::set_identifier(std::string identifier)
{
   this->identifier = identifier;
}


std::string &AddActor2D::get_identifier_ref()
{
   return identifier;
}


std::string AddActor2D::get_identifier() const
{
   return identifier;
}
} // namespace Messages
} // namespace MotionComposer
} // namespace AllegroFlare


