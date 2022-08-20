#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Network2
   {
      class Message
      {
      private:
         static int HEADER_LENGTH;
         static int MAX_BODY_LENGTH;
         std::string data;

      public:
         Message();
         ~Message();

         static int get_HEADER_LENGTH();
         static int get_MAX_BODY_LENGTH();
         std::string get_data();
         char* data_ptr();
         void ignore();
      };
   }
}



