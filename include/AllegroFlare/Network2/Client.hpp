#pragma once


#include <atomic>


namespace AllegroFlare
{
   namespace Network2
   {
      class Client
      {
      private:
         std::atomic<bool> *global_abort;

      public:
         Client(std::atomic<bool> *global_abort=nullptr);
         ~Client();

         void run_blocking_while_awaiting_abort();
      };
   }
}



