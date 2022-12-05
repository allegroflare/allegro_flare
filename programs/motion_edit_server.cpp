#include <allegro5/allegro.h>
#include <AllegroFlare/Network2/Server.hpp>
#include <AllegroFlare/StringFormatValidator.hpp>

int main(int argc, char **argv)
{
   std::atomic<bool> global_abort = false;
   //std::vector<std::string> messages_queue = {};
   //std::mutex messages_queue_mutex;

   AllegroFlare::Network2::Server server(&global_abort);

   // NOTE: might be able to use ngrok like this, for example:
   //client.set_host("6.tcp.ngrok.io");
   if (argc > 1)
   {
      std::string port_num_argument = argv[1];
      AllegroFlare::StringFormatValidator string_format_validator(port_num_argument);
      if (!string_format_validator.fits_max_length(4))
      {
         throw std::invalid_argument("[programs/motion_edit_server]: error: Invalid argument for port (error 1)");
      }
      if (!string_format_validator.has_only_numerical_characters())
      {
         throw std::invalid_argument("[programs/motion_edit_server]: error: Invalid argument for port (error 2)");
      }
      server.set_port(port_num_argument);
   }
   //client.set_port("13981");

   server.run_blocking_while_awaiting_abort();

   return 0;
}

