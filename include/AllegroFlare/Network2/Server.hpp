#pragma once


#include <atomic>
#include <string>



//#include <AllegroFlare/Network2/inc/chat_message.hpp> // just for BODY_LENGTH_MAX
#include <AllegroFlare/Network2/Message.hpp>


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
         static constexpr std::size_t BODY_LENGTH_MAX = AllegroFlare::Network2::Message::MAX_BODY_LENGTH;
         static constexpr const char* DEFAULT_PORT = "5432";

         Server(std::atomic<bool> *global_abort=nullptr);
         ~Server();

         void set_port(std::string port=DEFAULT_PORT);
         void run_blocking_while_awaiting_abort();
         std::string get_port();
      };
   }
}



