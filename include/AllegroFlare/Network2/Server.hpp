#pragma once


#include <atomic>


namespace AllegroFlare
{
   namespace Network2
   {
      class Server
      {
      private:
         std::atomic<bool> *global_abort;
         void run_blocking();

      public:
         Server(std::atomic<bool> *global_abort=nullptr);
         ~Server();

         void run_blocking_while_awaiting_abort();
         //void run_blocking();
      };
   }
}



