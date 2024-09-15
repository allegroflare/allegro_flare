#pragma once


#include <cstdint>
#include <filesystem>


namespace AllegroFlare
{
   namespace Testing
   {
      class TemporaryDirectoryCreator
      {
      private:

      protected:


      public:
         TemporaryDirectoryCreator();
         ~TemporaryDirectoryCreator();

         std::filesystem::path find_nonexistent_temporary_directory(uint32_t max_tries=100000);
         std::filesystem::path create(uint32_t max_tries=100000);
      };
   }
}



