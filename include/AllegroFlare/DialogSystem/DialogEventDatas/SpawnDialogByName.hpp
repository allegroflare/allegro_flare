#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace DialogEventDatas
      {
         class SpawnDialogByName : public AllegroFlare::GameEventDatas::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/DialogEventDatas/SpawnDialogByName";

         private:
            std::string name;

         protected:


         public:
            SpawnDialogByName(std::string name="[unset-name]");
            ~SpawnDialogByName();

            std::string get_name() const;
         };
      }
   }
}



