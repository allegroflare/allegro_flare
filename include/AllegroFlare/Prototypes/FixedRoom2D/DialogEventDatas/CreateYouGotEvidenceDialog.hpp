#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         namespace DialogEventDatas
         {
            class CreateYouGotEvidenceDialog : public AllegroFlare::GameEventDatas::Base
            {
            public:
               static constexpr char* TYPE = "DialogEventDatas/CreateYouGotEvidenceDialog";

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
}



