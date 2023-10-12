#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Testing
   {
      class TemporaryFilenameCreator
      {
      private:

      protected:


      public:
         TemporaryFilenameCreator();
         ~TemporaryFilenameCreator();

         std::string create_filename();
         std::string create_within_guaranteed_unique_directory();
      };
   }
}



