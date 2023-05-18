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

      private:

      protected:


      public:
         YAMLLoader();
         ~YAMLLoader();

         AllegroFlare::DialogTree::Node* load(std::string yaml_as_string="");
      };
   }
}



