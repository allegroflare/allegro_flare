#pragma once


#include <atomic>
#include <vector>
#include <string>
#include <mutex>


#include <AllegroFlare/Network2/inc/chat_message.hpp> // just for MESSAGE_BODY_LENGTH_MAX


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
         static constexpr std::size_t MESSAGE_BODY_LENGTH_MAX = chat_message::max_body_length;

         Client(
            std::atomic<bool> *global_abort=nullptr,
            std::vector<std::string> *messages_queue=nullptr,
            std::mutex *messages_queue_mutex=nullptr,
            void (*callback)(std::string, void*)=nullptr,
            void *callback_passed_data=nullptr
         );

         ~Client();

         void set_host(std::string host="localhost");
         void set_port(std::string port="5432");

         void run_blocking_while_awaiting_abort();
      };
   }
}



