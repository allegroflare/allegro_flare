#pragma once


#include <string>


class BuildInfo
{
private:
   static std::string time_of_build;

protected:


public:
   BuildInfo();
   ~BuildInfo();

   static std::string get_time_of_build();
};



