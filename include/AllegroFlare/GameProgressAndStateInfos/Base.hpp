#pragma once


#include <string>


namespace AllegroFlare
{
   namespace GameProgressAndStateInfos
   {
      class Base
      {
      public:
         static constexpr char* DEFAULT_FILENAME = (char*)"./saves/save.json";
         static constexpr char* TYPE = (char*)"AllegroFlare/GameProgressAndStateInfos/Base";

      private:
         std::string type;
         std::string save_file_filename;

      protected:


      public:
         Base(std::string type=AllegroFlare::GameProgressAndStateInfos::Base::TYPE);
         virtual ~Base();

         void set_save_file_filename(std::string save_file_filename);
         std::string get_type() const;
         std::string get_save_file_filename() const;
         void save();
         void load();
         virtual std::string export_to_string();
         virtual void import_from_string(std::string data_string="[unset-data_string]");
         bool is_type(std::string possible_type="");
      };
   }
}



