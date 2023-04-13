#pragma once


#include <AllegroFlare/GameplayMechanics/Triggers/Base.hpp>


namespace AllegroFlare
{
   namespace GameplayMechanics
   {
      namespace Triggers
      {
         class Basic : public AllegroFlare::GameplayMechanics::Triggers::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/GameplayMechanics/Triggers/Basic";

         private:
            virtual void on_trigger() override;
            virtual void on_reset() override;

         protected:


         public:
            Basic();
            virtual ~Basic();

         };
      }
   }
}



