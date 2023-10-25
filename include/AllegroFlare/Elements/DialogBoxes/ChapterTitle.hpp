#pragma once


#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxes
      {
         class ChapterTitle : public AllegroFlare::Elements::DialogBoxes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/DialogBoxes/ChapterTitle";

         private:
            std::string title_text;
            float duration;

         protected:


         public:
            ChapterTitle(std::string title_text="[unset-title_text]", float duration=6.0f);
            virtual ~ChapterTitle();

            std::string get_title_text() const;
            float get_duration() const;
            virtual void update() override;
            virtual bool ready_to_auto_advance() override;
         };
      }
   }
}



