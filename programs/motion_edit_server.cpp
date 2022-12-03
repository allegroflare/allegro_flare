#include <allegro5/allegro.h>
#include <AllegroFlare/Network2/Server.hpp>

int main(int argc, char **argv)
{
   std::atomic<bool> global_abort = false;
   //std::vector<std::string> messages_queue = {};
   //std::mutex messages_queue_mutex;

   AllegroFlare::Network2::Server server(&global_abort);

   // NOTE: might be able to use ngrok like this, for example:
   //client.set_host("6.tcp.ngrok.io");
   //client.set_port("13981");

   server.run_blocking_while_awaiting_abort();

   return 0;
}

