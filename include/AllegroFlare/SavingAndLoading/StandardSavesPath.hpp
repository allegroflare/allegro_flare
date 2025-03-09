#pragma once


#include <string>


namespace AllegroFlare
{
   namespace SavingAndLoading
   {
      class StandardSavesPath
      {
      public:
         static constexpr char* DEFAULT_DATA_FOLDER_PATH = (char*)"[unset-data_folder_path]";

      private:

      protected:


      public:
         StandardSavesPath();
         ~StandardSavesPath();

         static std::string build_standard_path(std::string data_folder_path=DEFAULT_DATA_FOLDER_PATH);
      };
   }
}



