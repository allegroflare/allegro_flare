#pragma once


#include <atomic>
#include <vector>
#include <string>
#include <mutex>


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
         void (*callback)(std::string body);

      public:
         Client(
            std::atomic<bool> *global_abort=nullptr,
            std::vector<std::string> *messages_queue=nullptr,
            std::mutex *messages_queue_mutex=nullptr,
            void (*callback)(std::string body)=nullptr
         );

         ~Client();

         void run_blocking_while_awaiting_abort();
      };
   }
}



