#pragma once


#include <AllegroFlare/Random.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Generators
   {
      class PersonNameGenerator
      {
      private:
         AllegroFlare::Random random;
         bool initialized;
         std::vector<std::string> victorian_boy_names;
         std::vector<std::string> victorian_girl_names;
         int next_boy_name_index;
         int next_girl_name_index;

      public:
         PersonNameGenerator();
         ~PersonNameGenerator();

         void initialize();
         void randomize(unsigned int seed=(unsigned int)time(0));
         std::string generate_boy_name();
         std::string generate_girl_name();
         static std::vector<std::string> build_victorian_boy_name_list();
         static std::vector<std::string> build_victorian_girl_name_list();
      };
   }
}



