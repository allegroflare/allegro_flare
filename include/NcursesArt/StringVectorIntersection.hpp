#pragma once


#include <string>
#include <vector>


namespace NcursesArt
{
   class StringVectorIntersection
   {
   private:
      std::vector<std::string> v1;
      std::vector<std::string> v2;

   public:
      StringVectorIntersection(std::vector<std::string> v1={}, std::vector<std::string> v2={});
      ~StringVectorIntersection();

      std::vector<std::string> intersection();
   };
}



