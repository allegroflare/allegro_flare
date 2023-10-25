

#include <AllegroFlare/DialogSystem/CharacterFactory.hpp>

#include <AllegroFlare/DialogSystem/Characters/Basic.hpp>


namespace AllegroFlare
{
namespace DialogSystem
{


CharacterFactory::CharacterFactory()
{
}


CharacterFactory::~CharacterFactory()
{
}


AllegroFlare::DialogSystem::Characters::Basic* CharacterFactory::create_basic_character(std::string display_name, std::string feature_description, std::string avatar_thumbnail_identifier, std::string avatar_portrait_identifier)
{
   AllegroFlare::DialogSystem::Characters::Basic *result = new AllegroFlare::DialogSystem::Characters::Basic();
   result->set_display_name(display_name);
   result->set_feature_description(feature_description);
   result->set_avatar_thumbnail_identifier(avatar_thumbnail_identifier);
   result->set_avatar_portrait_identifier(avatar_portrait_identifier);
   return result;
}


} // namespace DialogSystem
} // namespace AllegroFlare


