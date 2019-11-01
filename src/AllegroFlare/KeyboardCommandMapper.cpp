

#include <AllegroFlare/KeyboardCommandMapper.hpp>


KeyboardCommandMapper::KeyboardCommandMapper()
{}


KeyboardCommandMapper::~KeyboardCommandMapper()
{}


bool KeyboardCommandMapper::set_mapping(int al_keycode, bool shift, bool ctrl, bool alt, bool command, std::vector<std::string> command_identifiers)
{
   mapping[std::tuple<int, bool, bool, bool, bool>(al_keycode, shift, ctrl, alt, command)] = command_identifiers;
   return true;
}


std::vector<std::string> KeyboardCommandMapper::get_mapping(int al_keycode, bool shift, bool ctrl, bool alt, bool command)
{
   std::map<std::tuple<int, bool, bool, bool, bool>, std::vector<std::string>>::iterator mapper_iterator
      = mapping.find(std::tuple<int, bool, bool, bool, bool>(al_keycode, shift, ctrl, alt, command));

   if (mapper_iterator == mapping.end()) return {};

   return (*mapper_iterator).second;
}


