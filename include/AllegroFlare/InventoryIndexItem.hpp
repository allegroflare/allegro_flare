#pragma once


#include <string>
#include <tuple>


namespace AllegroFlare
{
   class InventoryIndexItem
   {
   private:
      std::string title;
      std::string bitmap_filename;
      std::string description;

   protected:


   public:
      InventoryIndexItem(std::string title="[unset-title]", std::string bitmap_filename="[unset-bitmap_filename]", std::string description="[unset-description]");
      ~InventoryIndexItem();

      void set_title(std::string title);
      void set_bitmap_filename(std::string bitmap_filename);
      void set_description(std::string description);
      std::string get_title() const;
      std::string get_bitmap_filename() const;
      std::string get_description() const;
      std::tuple<std::string, std::string, std::string> to_tuple();
   };
}



