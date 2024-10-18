#pragma once


#include <AllegroFlare/AssetStudio/Record.hpp>
#include <AllegroFlare/CSVParser.hpp>
#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace AssetStudio
   {
      class DatabaseCSVLoader : public AllegroFlare::CSVParser
      {
      private:
         std::string csv_full_path;
         std::vector<AllegroFlare::AssetStudio::Record> records;
         bool loaded;
         bool records_loaded;
         static std::vector<std::string> split(std::string string="", char delimiter=' ');
         static std::vector<std::string> tokenize(std::string str="", char delim='|');
         static std::string trim(std::string s="");

      protected:


      public:
         DatabaseCSVLoader();
         ~DatabaseCSVLoader();

         void set_csv_full_path(std::string csv_full_path);
         std::string get_csv_full_path() const;
         bool get_initialized();
         bool csv_file_exists();
         std::size_t num_records();
         std::vector<AllegroFlare::AssetStudio::Record> get_records();
         bool record_exists(std::string asset_identifier="[unset-asset_identifier]");
         AllegroFlare::AssetStudio::Record obtain_record_as_copy(std::string asset_identifier="[unset-asset_identifier]");
         AllegroFlare::AssetStudio::Record* find_record(std::string identifier="[unset-identifier]");
         static int toi(std::string value="[unset-value]");
         static float tof(std::string value="[unset-value]");
         static std::vector<std::string> comma_separated_quoted_strings_to_vector_of_strings(std::string comma_separated_quoted_strings="[unset-comma_separated_quoted_strings]");
         static std::vector<std::string> comma_separated_strings_to_vector_of_strings(std::string comma_separated_strings="[unset-comma_separated_strings]");
         std::pair<bool, uint32_t> str_to_playmode(std::string playmode_string="[unset-playmode_string]");
         static std::string validate_key_and_return(std::map<std::string, std::string>* extracted_row=nullptr, std::string key="[unset-key]");
         void load_records();
      };
   }
}



