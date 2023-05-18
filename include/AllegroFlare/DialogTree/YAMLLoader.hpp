#pragma once


#include <AllegroFlare/DialogTree/Node.hpp>
#include <AllegroFlare/YAMLValidator.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogTree
   {
      class YAMLLoader : public AllegroFlare::YAMLValidator
      {
      public:
         static constexpr char* SPEAKER_KEY = (char*)"speaker";
         static constexpr char* PAGES_KEY = (char*)"pages";
         static constexpr char* OPTIONS_KEY = (char*)"options";

      private:

      protected:


      public:
         YAMLLoader();
         ~YAMLLoader();

         AllegroFlare::DialogTree::Node* load(std::string yaml_as_string="");
      };
   }
}



