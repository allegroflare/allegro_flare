#pragma once


#include <cstdio>


class NetworkMessage
{
public:
   enum { header_length = 4 };
   enum { header_hash_length = 16 };
   enum { max_body_length = 512 };

private:
   char data_[header_length + max_body_length];
   std::size_t body_length;
   int sender_id;
   int recipient_id;

public:

   NetworkMessage();
   const char* data() const;
   char* data();
   std::size_t length() const;
   const char* body() const;
   char* body();

   std::size_t get_body_length() const;
   void set_body_length(std::size_t new_length);

   bool decode_header();
   void encode_header();
   int get_recipient_id() const;
   void set_recipient_id(int intended_recipient_id);
   int get_sender_id() const;
   void set_sender_id(int new_sender_id);
};


