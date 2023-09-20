#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace DialogEventDatas
      {
         class CloseDialog : public AllegroFlare::GameEventDatas::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/DialogEventDatas/CloseDialog";

         private:
            std::string property;

         protected:


         public:
            CloseDialog(std::string property="[unset-property]");
            ~CloseDialog();

            std::string get_property() const;
            bool property_is(std::string possible_type="");
         };
      }
   }
}



