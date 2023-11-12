

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


void Base::set_staged_character_expression(std::string staged_character_identifier, std::string expression, float time_now)
{
   return;
}

void Base::enter_character(std::string staged_character_identifier)
{
   // To Implement
   return;
}

void Base::exit_character(std::string staged_character_identifier)
{
   // To Implement
   return;
}

void Base::set_speaking_character_bitmap(ALLEGRO_BITMAP* speaking_character_bitmap, float time_now)
{
   throw std::runtime_error("---- no longer implemented, remove from derived classes ----");
   // TODO: This test is used in some derived classes. For now, moving it here as part of refactor
   return;
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


