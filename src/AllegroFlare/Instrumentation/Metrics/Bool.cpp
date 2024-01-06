

#include <AllegroFlare/Instrumentation/Metrics/Bool.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Instrumentation
{
namespace Metrics
{


Bool::Bool()
   : metrics(false)
   , size(64*4)
   , head(0)
   , initialized(false)
{
}


Bool::~Bool()
{
}


int Bool::get_size() const
{
   return size;
}


int Bool::get_head() const
{
   return head;
}


std::vector<bool> &Bool::get_metrics_ref()
{
   return metrics;
}


void Bool::set_size(int size)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Bool::set_size]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Bool::set_size: error: guard \"(!initialized)\" not met");
   }
   if (!((size >= 32)))
   {
      std::stringstream error_message;
      error_message << "[Bool::set_size]: error: guard \"(size >= 32)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Bool::set_size: error: guard \"(size >= 32)\" not met");
   }
   this->size = size;
   return;
}

void Bool::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Bool::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Bool::initialize: error: guard \"(!initialized)\" not met");
   }
   metrics.reserve(size);
   metrics.resize(size);
   initialized = true;
   head = 0;
   return;
}

void Bool::capture(bool metric)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Bool::capture]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Bool::capture: error: guard \"initialized\" not met");
   }
   head++;
   if (head >= metrics.size()) head = 0;
   metrics[head] = metric;
   return;
}

int Bool::head_delta(int delta)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Bool::head_delta]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Bool::head_delta: error: guard \"initialized\" not met");
   }
   int pos = head + delta;
   while (pos < 0) pos += metrics.size();
   if (pos >= metrics.size()) pos = pos % metrics.size();
   return pos;
}

std::vector<bool> Bool::get_last_n_metrics(int count)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Bool::get_last_n_metrics]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Bool::get_last_n_metrics: error: guard \"initialized\" not met");
   }
   // TODO: Test this
   std::vector<bool> result;
   result.resize(count);
   for (int i=0; i<result.size(); i++)
   {
      int index = head_delta(-i);
      result[i] = metrics[index];
   };
   return result;
}


} // namespace Metrics
} // namespace Instrumentation
} // namespace AllegroFlare


