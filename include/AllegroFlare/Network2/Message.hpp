#pragma once


#include <cstddef>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Network2
   {
      class Message
      {
      public:
         static constexpr std::size_t HEADER_LENGTH = 16;
         static constexpr std::size_t MAX_BODY_LENGTH = 512;

      private:
         static std::string MAGIC_HEADER_CHUNK;
         std::string data;
         std::size_t body_length;

      public:
         Message();
         ~Message();

         static std::string get_MAGIC_HEADER_CHUNK();
         std::string get_data() const;
         std::size_t get_body_length() const;
         void todo();
         char* data_ptr();
         char* body_ptr();
         std::size_t length();
         void set_body_length(std::size_t new_length=0);
         void set_body(std::string content="");
         std::string get_header();
         std::string get_body();
         std::vector<std::string> decode_header_and_validate();
         std::vector<std::string> validate_body_hash();
         void encode_header();
         std::string first_4_chars_hash_of(std::string string_to_hash="");
         std::string body_size_base62();
         int decode_body_size_chunk();
         std::string extract_nth_header_chunk(int position=0);
         void ignore();
      };
   }
}



