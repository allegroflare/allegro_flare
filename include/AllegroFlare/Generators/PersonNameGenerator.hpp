#pragma once


#include <AllegroFlare/Random.hpp>
#include <cstdint>
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
         std::vector<std::string> double_consecutive_t_names;
         int next_boy_name_index;
         int next_girl_name_index;
         int double_consecutive_t_name_index;

      protected:


      public:
         PersonNameGenerator();
         ~PersonNameGenerator();

         void initialize();
         void randomize(uint32_t seed=(uint32_t)time(0));
         std::string generate_boy_name();
         std::string generate_girl_name();
         std::string generate_double_consecutive_t_name();
         static std::vector<std::string> build_double_consecutive_t_name_list();
         static std::vector<std::string> build_victorian_boy_name_list();
         static std::vector<std::string> build_victorian_girl_name_list();
      };
   }
}



