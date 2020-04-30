

#include <AllegroFlare/Network/NetworkMessage.hpp>

#include <cstring> // for strncat and memcpy
#include <cstdlib> // for std::atoi


NetworkMessage::NetworkMessage()
   : body_length(0)
   , sender_id(0)
   , recipient_id(0)
{
}


const char* NetworkMessage::data() const
{
   return data_;
}


char* NetworkMessage::data()
{
   return data_;
}


std::size_t NetworkMessage::length() const
{
   return header_length + body_length;
}


const char* NetworkMessage::body() const
{
   return data_ + header_length;
}


char* NetworkMessage::body()
{
   return data_ + header_length;
}


std::size_t NetworkMessage::get_body_length() const
{
   return body_length;
}


void NetworkMessage::set_body_length(std::size_t new_length)
{
   body_length = new_length;
   if (body_length > max_body_length)
      body_length = max_body_length;
}


bool NetworkMessage::decode_header()
{
   char header[header_length + 1] = "";
   std::strncat(header, data_, header_length);
   body_length = std::atoi(header);
   if (body_length > max_body_length)
   {
      body_length = 0;
      return false;
   }
   return true;
}


void NetworkMessage::encode_header()
{
   char header[header_length + 1] = "";
   std::sprintf(header, "%4d", static_cast<int>(body_length));
   std::memcpy(data_, header, header_length);
}


int NetworkMessage::get_recipient_id() const
{
   return recipient_id;
}


void NetworkMessage::set_recipient_id(int intended_recipient_id)
{
   recipient_id = intended_recipient_id;
}


int NetworkMessage::get_sender_id() const
{
   return sender_id;
}


void NetworkMessage::set_sender_id(int new_sender_id)
{
   sender_id = new_sender_id;
}


