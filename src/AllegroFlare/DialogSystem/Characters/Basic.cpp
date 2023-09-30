

#include <AllegroFlare/DialogSystem/Characters/Basic.hpp>




namespace AllegroFlare
{
namespace DialogSystem
{
namespace Characters
{


Basic::Basic(std::string display_name)
   : AllegroFlare::DialogSystem::Characters::Base(AllegroFlare::DialogSystem::Characters::Basic::TYPE)
   , display_name(display_name)
   , avatar_thumbnail_identifier("[unset-avatar_thumbnail_identifier]")
   , avatar_portrait_identifier("[unset-avatar_portrait_identifier]")
{
}


Basic::~Basic()
{
}


void Basic::set_display_name(std::string display_name)
{
   this->display_name = display_name;
}


void Basic::set_avatar_thumbnail_identifier(std::string avatar_thumbnail_identifier)
{
   this->avatar_thumbnail_identifier = avatar_thumbnail_identifier;
}


void Basic::set_avatar_portrait_identifier(std::string avatar_portrait_identifier)
{
   this->avatar_portrait_identifier = avatar_portrait_identifier;
}


std::string Basic::get_display_name() const
{
   return display_name;
}


std::string Basic::get_avatar_thumbnail_identifier() const
{
   return avatar_thumbnail_identifier;
}


std::string Basic::get_avatar_portrait_identifier() const
{
   return avatar_portrait_identifier;
}




} // namespace Characters
} // namespace DialogSystem
} // namespace AllegroFlare


