#pragma once


#include <atomic>
#include <string>


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
         Server(std::atomic<bool> *global_abort=nullptr);
         ~Server();

         void set_port(std::string port="5432");
         void run_blocking_while_awaiting_abort();
      };
   }
}



