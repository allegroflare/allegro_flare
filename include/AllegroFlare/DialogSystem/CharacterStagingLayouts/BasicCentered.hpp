#pragma once


#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Base.hpp>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace CharacterStagingLayouts
      {
         class BasicCentered : public AllegroFlare::DialogSystem::CharacterStagingLayouts::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/CharacterStagingLayouts/BasicCentered";

         private:

         protected:


         public:
            BasicCentered();
            virtual ~BasicCentered();

            virtual void update(float time_now=0.0f) override;
            virtual void render() override;
         };
      }
   }
}



