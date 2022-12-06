#pragma once


#include <AllegroFlare/InventoryDictionaryItems/Base.hpp>
#include <string>
#include <tuple>


namespace AllegroFlare
{
   namespace InventoryDictionaryItems
   {
      class ClassicItem : public AllegroFlare::InventoryDictionaryItems::Base
      {
      public:
         static constexpr char* TYPE = (char*)"InventoryDictionaryItems/ClassicItem";

      private:
         std::string title;
         std::string bitmap_filename;
         std::string description;

      protected:


      public:
         ClassicItem(std::string title="[unset-title]", std::string bitmap_filename="[unset-bitmap_filename]", std::string description="[unset-description]");
         ~ClassicItem();

         void set_title(std::string title);
         void set_bitmap_filename(std::string bitmap_filename);
         void set_description(std::string description);
         std::string get_title() const;
         std::string get_bitmap_filename() const;
         std::string get_description() const;
         std::tuple<std::string, std::string, std::string> to_tuple();
      };
   }
}



