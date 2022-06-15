

#include <AllegroFlare/KeyboardCommandMapper.hpp>

#include <AllegroFlare/BitFlags.hpp>


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


bool KeyboardCommandMapper::set_mapping(int al_keycode, int modifiers, std::vector<std::string> command_identifier)
{
   AllegroFlare::BitFlags flags(modifiers);
   return set_mapping(al_keycode, flags.has(SHIFT), flags.has(CTRL), flags.has(ALT), flags.has(COMMAND), command_identifier);
}


std::vector<std::string> KeyboardCommandMapper::get_mapping(int al_keycode, int modifiers)
{
   AllegroFlare::BitFlags flags(modifiers);
   return get_mapping(al_keycode, flags.has(SHIFT), flags.has(CTRL), flags.has(ALT), flags.has(COMMAND));
}


