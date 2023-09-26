#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace DialogEventDatas
      {
         class LoadDialogYAMLFile : public AllegroFlare::GameEventDatas::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/DialogEventDatas/LoadDialogYAMLFile";

         private:
            std::string yaml_filename;

         protected:


         public:
            LoadDialogYAMLFile(std::string yaml_filename="[unset-yaml_filename]");
            ~LoadDialogYAMLFile();

            std::string get_yaml_filename() const;
         };
      }
   }
}



