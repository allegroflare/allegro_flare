

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

void Base::show(float time_now)
{
   // TODO: Consider implementation
   return;
}

void Base::hide(float time_now)
{
   // TODO: Consider implementation
   return;
}

void Base::clear()
{
   // TODO: Consider implementation
   return;
}

void Base::render()
{
   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace CharacterStagingLayouts
} // namespace DialogSystem
} // namespace AllegroFlare


