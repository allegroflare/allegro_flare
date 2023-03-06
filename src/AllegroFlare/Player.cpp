

#include <AllegroFlare/Player.hpp>




namespace AllegroFlare
{


Player::Player(std::string name, uint32_t id)
   : name(name)
   , id(id)
{
}


Player::~Player()
{
}


void Player::set_name(std::string name)
{
   this->name = name;
}


void Player::set_id(uint32_t id)
{
   this->id = id;
}


std::string Player::get_name() const
{
   return name;
}


uint32_t Player::get_id() const
{
   return id;
}




} // namespace AllegroFlare


