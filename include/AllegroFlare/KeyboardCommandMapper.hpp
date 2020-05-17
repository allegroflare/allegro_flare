#pragma once


#include <map>
#include <string>
#include <tuple>
#include <vector>


class KeyboardCommandMapper
{
public:
   enum modifiers
   {
      NO_MODIFIER = 0x00,
      SHIFT = 0x01,
      CTRL = 0x02,
      ALT = 0x04,
      COMMAND = 0x08,
      OPTION = 0x10,
   };

private:
   std::map<std::tuple<int, bool, bool, bool, bool>, std::vector<std::string>> mapping;

public:
   KeyboardCommandMapper();
   ~KeyboardCommandMapper();

   bool set_mapping(int al_keycode, bool shift, bool ctrl, bool alt, bool command, std::vector<std::string> command_identifier);
   std::vector<std::string> get_mapping(int al_keycode, bool shift, bool ctrl, bool alt, bool command=false);

   bool set_mapping(int al_keycode, int modifiers, std::vector<std::string> command_identifier);
   std::vector<std::string> get_mapping(int al_keycode, int modifiers);
};


