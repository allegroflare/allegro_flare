#pragma once


#include <string>


namespace AllegroFlare
{
   namespace InventoryDictionaryItems
   {
      class Base
      {
      public:
         static constexpr char* TYPE = "InventoryDictionaryItems/Base";

      private:
         std::string type;

      protected:


      public:
         Base(std::string type=AllegroFlare::InventoryDictionaryItems::Base::TYPE);
         ~Base();

         std::string get_type() const;
         bool is_type(std::string possible_type="");
      };
   }
}



