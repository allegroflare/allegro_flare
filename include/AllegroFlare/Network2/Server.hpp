#pragma once


#include <atomic>
#include <string>



#include <AllegroFlare/Network2/inc/chat_message.hpp> // just for BODY_LENGTH_MAX


namespace AllegroFlare
{
   namespace Network2
   {
      class Server
      {
      private:
         std::atomic<bool> *global_abort;
         void run_blocking();
         std::string port;

      public:
         static constexpr std::size_t BODY_LENGTH_MAX = chat_message::max_body_length;

         Server(std::atomic<bool> *global_abort=nullptr);
         ~Server();

         void set_port(std::string port="5432");
         void run_blocking_while_awaiting_abort();
      };
   }
}



