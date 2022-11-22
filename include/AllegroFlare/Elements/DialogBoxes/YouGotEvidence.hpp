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
            static constexpr char* TYPE = "DialogBoxes/YouGotEvidence";

         private:
            std::string property;
            bool finished;

         protected:


         public:
            YouGotEvidence(std::string property="[unset-property]");
            virtual ~YouGotEvidence();

            std::string get_property() const;
            bool get_finished() const;
            virtual void update() override;
            void advance();
         };
      }
   }
}



