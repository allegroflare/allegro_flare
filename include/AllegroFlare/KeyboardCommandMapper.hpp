#pragma once


#include <map>
#include <string>
#include <tuple>
#include <vector>


class KeyboardCommandMapper
{
private:
   std::map<std::tuple<int, bool, bool, bool, bool>, std::vector<std::string>> mapping;

public:
   KeyboardCommandMapper();
   ~KeyboardCommandMapper();

   bool set_mapping(int al_keycode, bool shift, bool ctrl, bool alt, bool command, std::vector<std::string> comand_identifier);
   std::vector<std::string> get_mapping(int al_keycode, bool shift, bool ctrl, bool alt, bool command=false);
};


