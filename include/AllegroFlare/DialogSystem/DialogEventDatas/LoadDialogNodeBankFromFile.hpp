#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace DialogEventDatas
      {
         class LoadDialogNodeBankFromFile : public AllegroFlare::GameEventDatas::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/DialogEventDatas/LoadDialogNodeBankFromFile";

         private:
            std::string yaml_filename;

         protected:


         public:
            LoadDialogNodeBankFromFile(std::string yaml_filename="[unset-yaml_filename]");
            ~LoadDialogNodeBankFromFile();

            std::string get_yaml_filename() const;
         };
      }
   }
}



