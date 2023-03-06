

#include <AllegroFlare/Player.hpp>




namespace AllegroFlare
{


Player::Player(uint32_t id, std::string name)
   : id(id)
   , name(name)
{
}


Player::~Player()
{
}


void Player::set_id(uint32_t id)
{
   this->id = id;
}


void Player::set_name(std::string name)
{
   this->name = name;
}


uint32_t Player::get_id() const
{
   return id;
}


std::string Player::get_name() const
{
   return name;
}




} // namespace AllegroFlare


