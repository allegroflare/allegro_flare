#pragma once


#include <UnnamedGameFramework/Achievement.hpp>
#include <string>
#include <map>


class Achievements
{
private:
   std::map<std::string, std::pair<Achievement *, bool>> all_achievements;

public:
   Achievements();
   ~Achievements();

   void add(std::string name, Achievement *achievement);
   void check_all();
};


