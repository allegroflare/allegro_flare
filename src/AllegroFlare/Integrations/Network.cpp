

#include <AllegroFlare/Integrations/Network.hpp>
#include <AllegroFlare/Network2/Server.hpp>
#include <AllegroFlare/Network2/Client.hpp>


namespace AllegroFlare
{
namespace Integrations
{


Network::Network()
   : ::testing::Test()
   , global_abort(false)
{
}


Network::~Network()
{
}


std::atomic<bool>* Network::get_global_abort_ptr()
{
   return &global_abort;
}

void Network::SetUp()
{
   return;
}

void Network::TearDown()
{
   return;
}

void Network::run_server_blocking(std::atomic<bool>* global_abort)
{
   AllegroFlare::Network2::Server server(global_abort);
   server.run_blocking_while_awaiting_abort();
   return;
}

void Network::run_client_blocking(std::atomic<bool>* global_abort)
{
   std::vector<std::string> messages_queue;
   std::mutex messages_queue_mutex;
   AllegroFlare::Network2::Client client(global_abort, &messages_queue, &messages_queue_mutex);
   client.run_blocking_while_awaiting_abort();
   return;
}
} // namespace Integrations
} // namespace AllegroFlare


