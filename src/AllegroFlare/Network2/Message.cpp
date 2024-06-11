

#include <AllegroFlare/Network2/Message.hpp>

#include <AllegroFlare/EncoderDecoders/Base62.hpp>
#include <AllegroFlare/Network2/inc/chat_message.hpp>
#include <AllegroFlare/SHA2.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Network2
{


Message::Message()
   : data(HEADER_LENGTH+MAX_BODY_LENGTH, ' ')
   , body_length(0)
{
}


Message::~Message()
{
}


std::string Message::get_data() const
{
   return data;
}


std::size_t Message::get_body_length() const
{
   return body_length;
}


void Message::todo()
{
   // set guards for unexpected acces when header has not been encoded
   return;
}

char* Message::data_ptr()
{
   return data.data();
}

char* Message::body_ptr()
{
   return data.data() + HEADER_LENGTH;
}

std::size_t Message::length()
{
   return HEADER_LENGTH + body_length;
}

void Message::set_body_length(std::size_t new_length)
{
   if (!((!(new_length > MAX_BODY_LENGTH))))
   {
      std::stringstream error_message;
      error_message << "[Message::set_body_length]: error: guard \"(!(new_length > MAX_BODY_LENGTH))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Message::set_body_length: error: guard \"(!(new_length > MAX_BODY_LENGTH))\" not met");
   }
   body_length = new_length;
   return;
}

void Message::set_body(std::string content)
{
   if (!((!(content.size() > MAX_BODY_LENGTH))))
   {
      std::stringstream error_message;
      error_message << "[Message::set_body]: error: guard \"(!(content.size() > MAX_BODY_LENGTH))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Message::set_body: error: guard \"(!(content.size() > MAX_BODY_LENGTH))\" not met");
   }
   set_body_length(content.size());
   std::memcpy(data_ptr() + HEADER_LENGTH, content.c_str(), body_length);
   return;
}

std::string Message::get_header()
{
   return data.substr(0, HEADER_LENGTH);
}

std::string Message::get_body()
{
   return data.substr(HEADER_LENGTH, body_length);
}

std::vector<std::string> Message::decode_header_and_validate()
{
   std::vector<std::string> error_messages;
   std::string header = get_header();

   // validate magic header chunk matches
   // TODO: test this condition
   if (header.substr(0, 4) != MAGIC_HEADER_CHUNK) error_messages.push_back("Magic header chunk does not match.");

   // TODO: validate the second chunk does decode
   // TODO: test this condition
   int decoded_body_size = decode_body_size_chunk();

   // Validate the second chunk value not larger than MAX_BODY_SIZE
   // TODO: test this condition
   if (decoded_body_size > MAX_BODY_LENGTH) error_messages.push_back("Body size value in header is too large");

   // Generate the expected value of the third chunk and ensure it matches the existing one
   // TODO: test this condition
   std::string first_8 = extract_nth_header_chunk(0) + extract_nth_header_chunk(1);
   std::string expected_third_chunk_value = first_4_chars_hash_of(first_8);
   if (expected_third_chunk_value != extract_nth_header_chunk(2))
       error_messages.push_back("Third chunk does not match an expected hash.");

   if (!error_messages.empty()) return error_messages;

   // set the body size to mach the header body size
   // TODO: test this new body size is a size matching the header
   set_body_length(decoded_body_size);

   return error_messages;
}

std::vector<std::string> Message::validate_body_hash()
{
   std::vector<std::string> error_messages;
   std::string expected_fourth_chunk_value = first_4_chars_hash_of(get_body());
   if (expected_fourth_chunk_value != extract_nth_header_chunk(3))
       error_messages.push_back("Fourth chunk does not match the expected hash of the body.");
   return error_messages;
}

void Message::encode_header()
{
   // header is in the following format:
   // 4 chars, special block with the characters "AFNM" for "AllegroFlare network message"
   // 4 chars, size of the data block in base62 (not base64) (with the lowercase first)
   // 4 chars, the first 4 characters of a hash. This hash is of the first 8 characters of the header
   // 4 chars, the first 4 characters of a hash of the whole body

   char header[HEADER_LENGTH + 1] = "";


   std::string first_8 = std::string(MAGIC_HEADER_CHUNK) + body_size_base62();

   std::snprintf(header,    5, "%s", MAGIC_HEADER_CHUNK); //.c_str());
   std::snprintf(header+4,  5, "%s", body_size_base62().c_str());
   std::snprintf(header+8,  5, "%s", first_4_chars_hash_of(first_8).c_str());
   std::snprintf(header+12, 5, "%s", first_4_chars_hash_of(get_body()).c_str());

   std::memcpy(data_ptr(), header, HEADER_LENGTH);
   return;
}

std::string Message::first_4_chars_hash_of(std::string string_to_hash)
{
   AllegroFlare::SHA2 sha2;
   return sha2.generate_sha224_hash(string_to_hash).substr(0, 4);
}

std::string Message::body_size_base62()
{
   AllegroFlare::EncoderDecoders::Base62 base62_encoder;
   return base62_encoder.encode(body_length, 4);
}

int Message::decode_body_size_chunk()
{
   AllegroFlare::EncoderDecoders::Base62 base62_encoder;
   return base62_encoder.decode(extract_nth_header_chunk(1));
}

std::string Message::extract_nth_header_chunk(int position)
{
   return data.substr(position * 4, 4);
}

void Message::ignore()
{
   return;
}


} // namespace Network2
} // namespace AllegroFlare


