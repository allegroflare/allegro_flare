#pragma once


#include <AllegroFlare/YAMLValidator.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogTree
   {
      class YAMLLoader : public AllegroFlare::YAMLValidator
      {
      private:

      protected:


      public:
         YAMLLoader();
         ~YAMLLoader();

         bool load(std::string yaml_string="");
      };
   }
}



