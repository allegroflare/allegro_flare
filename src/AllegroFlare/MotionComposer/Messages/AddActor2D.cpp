

#include <AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>



namespace AllegroFlare
{
namespace MotionComposer
{
namespace Messages
{


AddActor2D::AddActor2D(std::string identifier, std::string script)
   : AllegroFlare::MotionComposer::Messages::Base("AddActor2D")
   , identifier(identifier)
   , script(script)
{
}


AddActor2D::~AddActor2D()
{
}


void AddActor2D::set_identifier(std::string identifier)
{
   this->identifier = identifier;
}


void AddActor2D::set_script(std::string script)
{
   this->script = script;
}


std::string &AddActor2D::get_identifier_ref()
{
   return identifier;
}


std::string &AddActor2D::get_script_ref()
{
   return script;
}


std::string AddActor2D::get_identifier() const
{
   return identifier;
}

std::string AddActor2D::get_script() const
{
   return script;
}
} // namespace Messages
} // namespace MotionComposer
} // namespace AllegroFlare


