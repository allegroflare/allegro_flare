#pragma once


#include <AllegroFlare/InventoryDictionaryItems/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace InventoryDictionaryItems
   {
      class WithAttributes : public AllegroFlare::InventoryDictionaryItems::Base
      {
      public:
         static constexpr char* TYPE = "InventoryDictionaryItems/WithAttributes";

      private:
         std::string property;

      protected:


      public:
         WithAttributes(std::string property="[unset-property]");
         ~WithAttributes();

         std::string get_property() const;
         bool property_is(std::string possible_type="");
      };
   }
}



