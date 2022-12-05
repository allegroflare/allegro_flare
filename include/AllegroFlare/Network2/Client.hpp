#pragma once


#include <atomic>
#include <vector>
#include <string>
#include <mutex>


//#include <AllegroFlare/Network2/inc/chat_message.hpp> // just for MESSAGE_BODY_LENGTH_MAX
#include <AllegroFlare/Network2/Message.hpp>


namespace AllegroFlare
{
   namespace Network2
   {
      class Client
      {
      private:
         std::atomic<bool> *global_abort;
         std::vector<std::string> *messages_queue;
         std::mutex *messages_queue_mutex;
         void (*callback)(std::string, void*);
         void *callback_passed_data;
         std::string host;
         std::string port;

      public:
         static constexpr std::size_t MESSAGE_BODY_LENGTH_MAX = AllegroFlare::Network2::Message::MAX_BODY_LENGTH;
         static constexpr const char* DEFAULT_PORT = "5432";
         static constexpr const char* DEFAULT_HOST = "localhost";

         Client(
            std::atomic<bool> *global_abort=nullptr,
            std::vector<std::string> *messages_queue=nullptr,
            std::mutex *messages_queue_mutex=nullptr,
            void (*callback)(std::string, void*)=nullptr,
            void *callback_passed_data=nullptr
         );

         ~Client();

         void set_host(std::string host=DEFAULT_HOST);
         void set_port(std::string port=DEFAULT_PORT);

         void run_blocking_while_awaiting_abort();
      };
   }
}



