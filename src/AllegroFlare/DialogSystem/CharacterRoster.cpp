

#include <AllegroFlare/DialogSystem/CharacterRoster.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogSystem
{


CharacterRoster::CharacterRoster()
   : characters({})
{
}


CharacterRoster::~CharacterRoster()
{
}


void CharacterRoster::set_characters(std::map<std::string, AllegroFlare::DialogSystem::Characters::Base*> characters)
{
   this->characters = characters;
}


std::map<std::string, AllegroFlare::DialogSystem::Characters::Base*> &CharacterRoster::get_characters_ref()
{
   return characters;
}


int CharacterRoster::num_characters()
{
   return characters.size();
}

std::vector<std::string> CharacterRoster::get_character_names()
{
   std::vector<std::string> result;
   for (auto &character : characters)
   {
      result.push_back(character.first);
   }
   return result;
}

void CharacterRoster::add_character(std::string name, AllegroFlare::DialogSystem::Characters::Base* character)
{
   if (!(character))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DialogSystem::CharacterRoster::add_character]: error: guard \"character\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DialogSystem::CharacterRoster::add_character]: error: guard \"character\" not met");
   }
   if (!((!character_exists_by_name(name))))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DialogSystem::CharacterRoster::add_character]: error: guard \"(!character_exists_by_name(name))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DialogSystem::CharacterRoster::add_character]: error: guard \"(!character_exists_by_name(name))\" not met");
   }
   characters[name] = character;
}

bool CharacterRoster::character_exists_by_name(std::string name)
{
   return (characters.find(name) != characters.end());
}

AllegroFlare::DialogSystem::Characters::Base* CharacterRoster::find_character_by_name(std::string name)
{
   if (!(character_exists_by_name(name)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DialogSystem::CharacterRoster::find_character_by_name]: error: guard \"character_exists_by_name(name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DialogSystem::CharacterRoster::find_character_by_name]: error: guard \"character_exists_by_name(name)\" not met");
   }
   // TODO: This guard results in a double lookup. Might be faster to integrate it below.
   if (characters.find(name) == characters.end()) return nullptr;
   return characters[name];
}


} // namespace DialogSystem
} // namespace AllegroFlare


