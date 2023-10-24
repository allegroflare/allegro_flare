#pragma once


#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxes
      {
         class Wait : public AllegroFlare::Elements::DialogBoxes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/DialogBoxes/Wait";

         private:
            float duration;
            float started_at;

         protected:


         public:
            Wait(float duration=1.0, float started_at=1.0);
            virtual ~Wait();

            void set_duration(float duration);
            float get_duration() const;
            float get_started_at() const;
            virtual bool ready_to_auto_advance() override;
            virtual void update() override;
         };
      }
   }
}



