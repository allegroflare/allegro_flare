

#include <AllegroFlare/Network2/Message.hpp>
#include <stdexcept>
#include <sstream>
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

char* Message::body_ptr()
{
   return data.data() + HEADER_LENGTH;
}

std::size_t Message::length()
{
   return HEADER_LENGTH + body_length;
}

void Message::ignore()
{
   return;
}
} // namespace Network2
} // namespace AllegroFlare


