

#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Base.hpp>




namespace AllegroFlare
{
namespace DialogSystem
{
namespace CharacterStagingLayouts
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


void Base::update(float time_now)
{
   return;
}

void Base::render()
{
   return;
}


} // namespace CharacterStagingLayouts
} // namespace DialogSystem
} // namespace AllegroFlare


