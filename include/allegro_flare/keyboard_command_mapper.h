#pragma once



#include <map>
#include <string>
#include <tuple>



class KeyboardCommandMapper
{
private:
   std::map<std::tuple<int, bool, bool, bool>, std::string> mapping;

public:
   KeyboardCommandMapper();
   ~KeyboardCommandMapper();

   bool set_mapping(int al_keycode, bool shift, bool ctrl, bool alt, std::string comand_identifier);
   std::string get_mapping(int al_keycode, bool shift, bool ctrl, bool alt);
};



