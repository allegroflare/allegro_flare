

#include <AllegroFlare/Integrations/Network.hpp>



namespace AllegroFlare
{
namespace Integrations
{


Network::Network(AllegroFlare::Network2::Server server)
   : ::testing::Test()
   , server(server)
   , global_abort(false)
{
}


Network::~Network()
{
}


void Network::set_server(AllegroFlare::Network2::Server server)
{
   this->server = server;
}


AllegroFlare::Network2::Server Network::get_server()
{
   return server;
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
   //sleep(2);
   AllegroFlare::Network2::Server server(global_abort);
   //server.run_blocking();
   return;
}

void Network::run_client_blocking()
{
   sleep(1);
   //AllegroFlare::Network2::Client client(&global_abort);
   //server.run_blocking();
   return;
}
} // namespace Integrations
} // namespace AllegroFlare


