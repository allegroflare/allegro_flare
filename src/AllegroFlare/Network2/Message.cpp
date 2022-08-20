

#include <AllegroFlare/Network2/Message.hpp>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/EncoderDecoders/Base62.hpp>
#include <AllegroFlare/Network2/inc/chat_message.hpp>


namespace AllegroFlare
{
namespace Network2
{


std::size_t Message::HEADER_LENGTH = 16;


std::size_t Message::MAX_BODY_LENGTH = 512;


Message::Message()
   : data(16+512, ' ')
   , body_length(0)
{
}


Message::~Message()
{
}


std::size_t Message::get_HEADER_LENGTH()
{
   return HEADER_LENGTH;
}


std::size_t Message::get_MAX_BODY_LENGTH()
{
   return MAX_BODY_LENGTH;
}


std::string Message::get_data()
{
   return data;
}


std::size_t Message::get_body_length()
{
   return body_length;
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
         error_message << "Message" << "::" << "set_body_length" << ": error: " << "guard \"(!(new_length > MAX_BODY_LENGTH))\" not met";
         throw std::runtime_error(error_message.str());
      }
   body_length = new_length;
   return;
}

std::string Message::get_header()
{
   return data.substr(0, HEADER_LENGTH);
}

void Message::encode_header()
{
   // header is in the following format:
   // 4 chars, special block with the characters "AFNM" for "AllegroFlare network message"
   // 4 chars, size of the data block in base62 (not base64) (with the lowercase first)
   // 4 chars, the first 4 characters of a hash. This hash is of the first 8 characters of the header
   // 4 chars, the first 4 characters of a hash of the whole body

   char header[16 + 1] = ""; // eeks, here "16" is used rather than HEADER_LENGTH because constexpr is not
                             // supported in quintessence
   std::sprintf(header,    "AFNM");
   std::sprintf(header+4,  body_size_base62().c_str());
   std::sprintf(header+8,  first_4_chars_hash_of().c_str());
   std::sprintf(header+12, first_4_chars_hash_of().c_str());

   std::memcpy(data_ptr(), header, HEADER_LENGTH);
   return;
}

std::string Message::first_4_chars_hash_of(std::string string_to_hash)
{
   return "TODO";
}

std::string Message::body_size_base62()
{
   AllegroFlare::EncoderDecoders::Base62 base62_encoder;
   std::stringstream ss;
      //ss << std::setfill('0') << std::setw(4) << base62_encoder.encode(body_length);
   return ss.str();
}

void Message::ignore()
{
   return;
}
} // namespace Network2
} // namespace AllegroFlare


