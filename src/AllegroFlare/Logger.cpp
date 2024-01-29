

#include <AllegroFlare/Logger.hpp>

#include <AllegroFlare/ConsoleColors.hpp>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


std::set<std::string> Logger::once_emitted_warnings = {};


std::string Logger::log_filename = DEFAULT_LOG_FILENAME;


std::ofstream Logger::log_file = {};


bool Logger::log_file_initialized = false;


std::string Logger::instrumentation_log_filename = DEFAULT_INSTRUMENTATION_LOG_FILENAME;


std::ofstream Logger::instrumentation_log_file = {};


bool Logger::instrumentation_log_file_initialized = false;


AllegroFlare::Logger* Logger::instance = nullptr;


Logger::Logger()
{
}


Logger::~Logger()
{
}


void Logger::set_instance(AllegroFlare::Logger* instance_to_use)
{
   if (!((!instance)))
   {
      std::stringstream error_message;
      error_message << "[Logger::set_instance]: error: guard \"(!instance)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logger::set_instance: error: guard \"(!instance)\" not met");
   }
   instance = instance_to_use;
   return;
}

void Logger::clear_instance()
{
   instance = nullptr;
   return;
}

bool Logger::has_instance()
{
   return (instance != nullptr);
}

void Logger::set_log_filename(std::string log_filename)
{
   if (!((!log_file_initialized)))
   {
      std::stringstream error_message;
      error_message << "[Logger::set_log_filename]: error: guard \"(!log_file_initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logger::set_log_filename: error: guard \"(!log_file_initialized)\" not met");
   }
   this->log_filename = log_filename;
   return;
}

void Logger::initialize_log_file()
{
   if (!((!log_file_initialized)))
   {
      std::stringstream error_message;
      error_message << "[Logger::initialize_log_file]: error: guard \"(!log_file_initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logger::initialize_log_file: error: guard \"(!log_file_initialized)\" not met");
   }
   log_file.open(log_filename);
   if (!log_file.is_open()) {
      std::string error_message = build_error_message(
            "AllegroFlare::Logger::initialize_log_file",
            "Could not open log file for writing. Expecting to open() on filename \"" + log_filename + "\"."
         );
      // TODO: throw std::runtime_error(error_message.str());
   }
   log_file_initialized = true;
   return;
}

void Logger::close_log_file()
{
   if (!((log_file_initialized)))
   {
      std::stringstream error_message;
      error_message << "[Logger::close_log_file]: error: guard \"(log_file_initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logger::close_log_file: error: guard \"(log_file_initialized)\" not met");
   }
   log_file.close();
   if (log_file.is_open()) {
      std::string error_message = build_error_message(
            "AllegroFlare::Logger::close_log_file",
            "Attempted not open log file for writing. Expecting to open() on filename \"" + log_filename + "\"."
         );
      // TODO: throw std::runtime_error(error_message.str());
   }
   log_file_initialized = false;
   return;
}

void Logger::set_instrumentation_log_filename(std::string instrumentation_log_filename)
{
   if (!((!instrumentation_log_file_initialized)))
   {
      std::stringstream error_message;
      error_message << "[Logger::set_instrumentation_log_filename]: error: guard \"(!instrumentation_log_file_initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logger::set_instrumentation_log_filename: error: guard \"(!instrumentation_log_file_initialized)\" not met");
   }
   this->instrumentation_log_filename = instrumentation_log_filename;
   return;
}

void Logger::initialize_instrumentation_log_file()
{
   if (!((!instrumentation_log_file_initialized)))
   {
      std::stringstream error_message;
      error_message << "[Logger::initialize_instrumentation_log_file]: error: guard \"(!instrumentation_log_file_initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logger::initialize_instrumentation_log_file: error: guard \"(!instrumentation_log_file_initialized)\" not met");
   }
   instrumentation_log_file.open(instrumentation_log_filename, std::ofstream::out | std::ofstream::app);
   if (!instrumentation_log_file.is_open()) {
      std::string error_message = build_error_message(
            "AllegroFlare::Logger::initialize_instrumentation_log_file",
            "Could not open instrumentation_log file for writing. Expecting to open() on filename \"" + instrumentation_log_filename + "\"."
         );
       throw std::runtime_error(error_message);
   }
   instrumentation_log_file_initialized = true;
   return;
}

void Logger::close_instrumentation_log_file()
{
   if (!((instrumentation_log_file_initialized)))
   {
      std::stringstream error_message;
      error_message << "[Logger::close_instrumentation_log_file]: error: guard \"(instrumentation_log_file_initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logger::close_instrumentation_log_file: error: guard \"(instrumentation_log_file_initialized)\" not met");
   }
   instrumentation_log_file.close();
   if (instrumentation_log_file.is_open()) {
      std::string error_message = build_error_message(
            "AllegroFlare::Logger::close_instrumentation_log_file",
            "Attempted not open instrumentation_log file for writing. Expecting to open() on filename \"" + instrumentation_log_filename + "\"."
         );
      throw std::runtime_error(error_message);
   }
   instrumentation_log_file_initialized = false;
   return;
}

void Logger::outstream_instrumentation_metric(AllegroFlare::Instrumentation::PrimaryProcessEventMetric* metric)
{
   if (!(instance))
   {
      std::stringstream error_message;
      error_message << "[Logger::outstream_instrumentation_metric]: error: guard \"instance\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logger::outstream_instrumentation_metric: error: guard \"instance\" not met");
   }
   if (!(instance->instrumentation_log_file_initialized))
   {
      std::stringstream error_message;
      error_message << "[Logger::outstream_instrumentation_metric]: error: guard \"instance->instrumentation_log_file_initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logger::outstream_instrumentation_metric: error: guard \"instance->instrumentation_log_file_initialized\" not met");
   }
   if (!(metric))
   {
      std::stringstream error_message;
      error_message << "[Logger::outstream_instrumentation_metric]: error: guard \"metric\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logger::outstream_instrumentation_metric: error: guard \"metric\" not met");
   }
   static const std::string div = "\t";
   //if (instance && instance->instrumentation_log_file_initialized)
   instance->instrumentation_log_file << metric->event_type
                               << div << metric->event_time
                               << div << metric->processing_start_time
                               << div << metric->processing_end_time
                               << div << metric->primary_timer_events_dropped
                               << div << metric->al_flip_display_start_time
                               << div << metric->al_flip_display_end_time
                                      << std::endl;
   //std::
   //std::stringstream result;
   //result << CONSOLE_COLOR_RED << "[" << from << "]: error: " << message << CONSOLE_COLOR_DEFAULT;
   //return result.str();
}

std::string Logger::build_error_message(std::string from, std::string message)
{
   std::stringstream result;
   result << CONSOLE_COLOR_RED << "[" << from << "]: error: " << message << CONSOLE_COLOR_DEFAULT;
   return result.str();
}

std::string Logger::build_guard_error_message(std::string from, std::string guard_statement)
{
   std::stringstream result;

   // TODO: I don't think there should be a newline at the end of this statement, but it exists in the blast error
   // message, and should probably be removed. Consider modifying the blast error message and removing it.
   result << CONSOLE_COLOR_RED << "[" << from << "]: error: guard \"" << guard_statement << "\" not met. "
          << "An exception will be thrown to halt the program." << CONSOLE_COLOR_DEFAULT
          << std::endl;
   return result.str();
}

std::string Logger::build_warning_message(std::string from, std::string message, bool is_warn_once)
{
   std::stringstream result;
   result << CONSOLE_COLOR_YELLOW << "[" << from << "]: warning";
   if (is_warn_once) result << " (once)";
   result << ": " << message << CONSOLE_COLOR_DEFAULT;
   return result.str();
}

std::string Logger::build_not_included_message(std::string element_not_present, std::vector<std::string> valid_elements)
{
   std::stringstream result;
   result << "The element "
          << quote_and_escape_inner_quotes(element_not_present)
          << " is not in the list of valid elements [";
   for (auto &valid_element : valid_elements)
   {
      valid_element = quote_and_escape_inner_quotes(valid_element);
   }
   result << join(valid_elements, ", ");
   result << "]";
   return result.str();
}

std::string Logger::build_unimplemented_for_base_class_message(std::string from)
{
   return build_error_message(from,
                              "This method is a virtual method an is expected to be implemented by the "
                              "derived class that is calling it"
                             );
}

std::string Logger::build_info_message(std::string from, std::string message)
{
   std::stringstream result;
   result << CONSOLE_COLOR_CYAN << "[" << from << "]: info: " << message << CONSOLE_COLOR_DEFAULT;
   return result.str();
}

std::string Logger::build_unhandled_case_message(std::string unhandled_case)
{
   std::stringstream result;
   result << "Unhandled case for case " << quote_and_escape_inner_quotes(unhandled_case) << ".";
   return result.str();
}

void Logger::throw_missing_file_error(std::string from, std::string filename, std::string filetype)
{
   std::stringstream error_message;
   std::string current_path = std::filesystem::current_path().string();

   error_message << "The expected " << filetype << " file does not exist. "
                 << "Looking for \"" << filename << "\" from the current path "
                 << "\"" << current_path << "\".";
   throw_error(from, error_message.str());
   return;
}

void Logger::throw_unimplemented_for_base_class_error(std::string from)
{
   // This is incorrect somehow, feel free to fix
   throw_error(from, build_unimplemented_for_base_class_message(from));
   return;
}

void Logger::info_from(std::string from, std::string message)
{
   std::string info_message = build_info_message(from, message);
   std::cout << info_message << std::endl;
   if (instance && instance->log_file_initialized) instance->log_file << info_message << std::endl;
}

void Logger::warn_from(std::string from, std::string message)
{
   std::string warning_message = build_warning_message(from, message);
   std::cout << warning_message << std::endl;
   if (instance && instance->log_file_initialized) instance->log_file << warning_message << std::endl;
}

void Logger::warn_from_once(std::string from, std::string message)
{
   std::string composite_message = build_warning_message(from, message, true);
   bool message_already_emitted = once_emitted_warnings.find(composite_message) != once_emitted_warnings.end();
   if (!message_already_emitted)
   {
      warn_from(from, message);
      once_emitted_warnings.insert(composite_message);
   }
}

void Logger::throw_error(std::string from, std::string message)
{
   std::stringstream error_message;
   error_message << "[" << from << "]: error: " << message;

   std::stringstream error_message_for_cout;
   error_message_for_cout << CONSOLE_COLOR_RED
                          << "[" << from << "] error: " << message
                          << CONSOLE_COLOR_DEFAULT << std::endl;

   std::cout << error_message_for_cout.str();

   throw std::runtime_error(error_message.str());
}

void Logger::error_from(std::string from, std::string message)
{
   // NOTE: "error_from" is the same as "throw_from" but does not throw.
   std::stringstream error_message;
   error_message << "[" << from << "]: error: " << message;

   std::stringstream error_message_for_cout;
   error_message_for_cout << CONSOLE_COLOR_RED
                          << "[" << from << "] error: " << message
                          << CONSOLE_COLOR_DEFAULT << std::endl;

   std::cout << error_message_for_cout.str();
   return;
}

void Logger::throw_unhandled_case(std::string from, std::string unhandled_case)
{
   std::stringstream error_message;
   std::string message = build_unhandled_case_message(unhandled_case);
   error_message << "[" << from << "]: error: " << message;

   std::stringstream error_message_for_cout;
   error_message_for_cout << CONSOLE_COLOR_RED
                          << "[" << from << "] error: " << message
                          << CONSOLE_COLOR_DEFAULT << std::endl;

   std::cout << error_message_for_cout.str();

   throw std::runtime_error(error_message.str());
}

std::string Logger::join(std::vector<std::string> tokens, std::string delimiter)
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

std::string Logger::quote_and_escape_inner_quotes(std::string subject)
{
   return "\"" + replace(subject, "\"", "\\\"") + "\"";
}

std::string Logger::replace(std::string subject, std::string search, std::string replace)
{
   std::string buffer;

   int sealeng = search.length();
   int strleng = subject.length();

   if (sealeng==0)
      return subject;//no change

   for(int i=0, j=0; i<strleng; j=0 )
   {
      while (i+j<strleng && j<sealeng && subject[i+j]==search[j])
         j++;
      if (j==sealeng)//found 'search'
      {
         buffer.append(replace);
         i+=sealeng;
      }
      else
      {
         buffer.append( &subject[i++], 1);
      }
   }
   subject = buffer;
   return subject;
}


} // namespace AllegroFlare


