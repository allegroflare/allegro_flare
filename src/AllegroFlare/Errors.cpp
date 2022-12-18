

#include <AllegroFlare/Errors.hpp>

#include <iostream>
#include <sstream>


namespace AllegroFlare
{


Errors::Errors()
{
}


Errors::~Errors()
{
}


std::string Errors::build_error_message(std::string from, std::string message)
{
   const std::string CONSOLE_COLOR_RED = "[1;31m";
   const std::string CONSOLE_COLOR_DEFAULT = "[0m";
   std::stringstream result;
   result << CONSOLE_COLOR_RED << "[" << from << "]: error: " << message << CONSOLE_COLOR_DEFAULT << std::endl;
   return result.str();
}

void Errors::throw_missing_file_error(std::string from, std::string filename, std::string filetype)
{
   std::stringstream error_message;
   error_message << "The expected " << filetype << " file does not exist. Looking in \"" << filename << "\"";
   throw_error(from, error_message.str());
   return;
}

void Errors::throw_error(std::string from, std::string message)
{
   std::stringstream error_message;
   error_message << "[" << from << "]: error: " << message;

   const std::string CONSOLE_COLOR_RED = "[1;31m";
   const std::string CONSOLE_COLOR_DEFAULT = "[0m";
   std::stringstream error_message_for_cout;
   error_message_for_cout << CONSOLE_COLOR_RED
                          << "[" << from << "] error: " << message
                          << CONSOLE_COLOR_DEFAULT << std::endl;

   std::cout << error_message_for_cout.str();

   throw std::runtime_error(error_message.str());
}


} // namespace AllegroFlare


