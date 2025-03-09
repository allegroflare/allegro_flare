#pragma once


#include <AllegroFlare/SavingAndLoading/SaveSlot.hpp>
#include <vector>


namespace AllegroFlare
{
   namespace SavingAndLoading
   {
      class SavingAndLoading
      {
      private:
         std::vector<AllegroFlare::SavingAndLoading::SaveSlot> save_slots;

      protected:


      public:
         SavingAndLoading();
         ~SavingAndLoading();

         void setup();
      };
   }
}



