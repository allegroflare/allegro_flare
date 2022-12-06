#pragma once


#include <AllegroFlare/Attributes.hpp>
#include <AllegroFlare/InventoryDictionaryItems/Base.hpp>


namespace AllegroFlare
{
   namespace InventoryDictionaryItems
   {
      class WithAttributes : public AllegroFlare::InventoryDictionaryItems::Base, public AllegroFlare::Attributes
      {
      public:
         static constexpr char* TYPE = (char*)"InventoryDictionaryItems/WithAttributes";

      private:

      protected:


      public:
         WithAttributes();
         ~WithAttributes();

      };
   }
}



