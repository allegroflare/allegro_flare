#include <allegro5/allegro.h>
#include <AllegroFlare/Network2/Server.hpp>
#include <AllegroFlare/StringFormatValidator.hpp>


const std::string ASCII_BANNER = R"END(
    __  _______  ______________  _   __   __________  __________
   /  |/  / __ \/_  __/  _/ __ \/ | / /  / ____/ __ \/  _/_  __/
  / /|_/ / / / / / /  / // / / /  |/ /  / __/ / / / // /  / /
 / /  / / /_/ / / / _/ // /_/ / /|  /  / /___/ /_/ // /  / /
/_/  /_/\____/ /_/ /___/\____/_/ |_/  /_____/_____/___/ /_/
   ___________ _   _________
  / __/ __/ _ \ | / / __/ _ \ ----------------------------------
 _\ \/ _// , _/ |/ / _// , _/ ---------------------------------
/___/___/_/|_||___/___/_/|_| ---------------------------------

)END";


const char *CYAN = "\033[1;34m";
const char *YELLOW = "\033[1;33m";
const char *MAGENTA = "\033[1;35m";
const char *DEFAULT = "\033[0m";
#include <sstream>

static std::vector<std::string> split(std::string text, char delimiter)
{
   std::vector<std::string> elems;
   auto result = std::back_inserter(elems);
   std::stringstream ss(text);
   std::string item;
   while (std::getline(ss, item, delimiter)) { *(result++) = item; }
   return elems;
}

std::string join(std::vector<std::string> tokens, std::string delimiter)
{
   std::stringstream result;
   bool last = false;
   for (unsigned i=0; i<tokens.size(); i++)
   {
      result << tokens[i];
      if (i == tokens.size()-1) last = true;
      if (!last) result << delimiter;
   }
   return result.str();
}

std::string stylize_banner(std::string text)
{
   std::vector<std::string> lines = split(text, '\n');
   for (auto &line : lines)
   {
      line = CYAN + line + DEFAULT;
   }
   return join(lines, "\n");
}

std::string yellow(std::string text)
{
   return YELLOW + text + DEFAULT;
}



#include <iostream>

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
      if (!string_format_validator.fits_min_length(4))
      {
         throw std::invalid_argument("[programs/motion_edit_server]: error: Invalid argument for port (error 1)");
      }
      if (!string_format_validator.fits_max_length(6))
      {
         throw std::invalid_argument("[programs/motion_edit_server]: error: Invalid argument for port (error 2)");
      }
      if (!string_format_validator.has_only_numerical_characters())
      {
         throw std::invalid_argument("[programs/motion_edit_server]: error: Invalid argument for port (error 3)");
      }
      server.set_port(port_num_argument);
   }

   std::cout << stylize_banner(ASCII_BANNER) << std::endl;
   std::cout << "   - Running on port: " << yellow(server.get_port()) << std::endl;
   std::cout << "   - Press Ctrl+C to abort." << std::endl;
   std::cout << std::endl;

   server.run_blocking_while_awaiting_abort();

   return 0;
}

