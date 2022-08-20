#pragma once


#include <cstddef>
#include <string>


namespace AllegroFlare
{
   namespace Network2
   {
      class Message
      {
      private:
         static std::size_t HEADER_LENGTH;
         static std::size_t MAX_BODY_LENGTH;
         std::string data;
         std::size_t body_length;

      public:
         Message();
         ~Message();

         static std::size_t get_HEADER_LENGTH();
         static std::size_t get_MAX_BODY_LENGTH();
         std::string get_data();
         std::size_t get_body_length();
         char* data_ptr();
         char* body_ptr();
         std::size_t length();
         void set_body_length(std::size_t new_length=0);
         std::string get_header();
         void encode_header();
         std::string first_4_chars_hash_of(std::string string_to_hash="");
         void ignore();
      };
   }
}



