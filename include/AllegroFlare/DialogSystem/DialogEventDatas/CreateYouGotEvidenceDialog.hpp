#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace DialogEventDatas
      {
         class CreateYouGotEvidenceDialog : public AllegroFlare::GameEventDatas::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/DialogEventDatas/CreateYouGotEvidenceDialog";

         private:
            std::string evidence_name;
            std::string evidence_bitmap_identifier;

         protected:


         public:
            CreateYouGotEvidenceDialog(std::string evidence_name="[unset-evidence_name]", std::string evidence_bitmap_identifier="[unset-evidence_bitmap_identifier]");
            ~CreateYouGotEvidenceDialog();

            std::string get_evidence_name() const;
            std::string get_evidence_bitmap_identifier() const;
         };
      }
   }
}



