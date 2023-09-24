#pragma once


#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxes
      {
         class YouGotEvidence : public AllegroFlare::Elements::DialogBoxes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"DialogBoxes/YouGotEvidence";

         private:
            std::string evidence_name;
            std::string evidence_bitmap_identifier;

         protected:


         public:
            YouGotEvidence(std::string evidence_name="[unset-evidence_name]", std::string evidence_bitmap_identifier="[unset-evidence_bitmap_identifier]");
            virtual ~YouGotEvidence();

            std::string get_evidence_name() const;
            std::string get_evidence_bitmap_identifier() const;
            virtual void start() override;
            virtual void update() override;
            virtual void advance() override;
         };
      }
   }
}



