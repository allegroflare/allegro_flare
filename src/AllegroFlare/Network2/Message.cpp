

#include <AllegroFlare/Network2/Message.hpp>
#include <AllegroFlare/Network2/inc/chat_message.hpp>


namespace AllegroFlare
{
namespace Network2
{


int Message::HEADER_LENGTH = 16;


int Message::MAX_BODY_LENGTH = 512;


Message::Message()
   : data(16+512, ' ')
{
}


Message::~Message()
{
}


int Message::get_HEADER_LENGTH()
{
   return HEADER_LENGTH;
}


int Message::get_MAX_BODY_LENGTH()
{
   return MAX_BODY_LENGTH;
}


std::string Message::get_data()
{
   return data;
}


char* Message::data_ptr()
{
   return data.data();
}

void Message::ignore()
{
   return;
}
} // namespace Network2
} // namespace AllegroFlare


