

#include <AllegroFlare/Instrumentation/Metrics/Double.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Instrumentation
{
namespace Metrics
{


Double::Double()
   : metrics(false)
   , size(64*4)
   , head(0)
   , initialized(false)
{
}


Double::~Double()
{
}


int Double::get_size() const
{
   return size;
}


int Double::get_head() const
{
   return head;
}


std::vector<double> &Double::get_metrics_ref()
{
   return metrics;
}


void Double::set_size(int size)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::Metrics::Double::set_size]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::Metrics::Double::set_size]: error: guard \"(!initialized)\" not met");
   }
   if (!((size >= 32)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::Metrics::Double::set_size]: error: guard \"(size >= 32)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::Metrics::Double::set_size]: error: guard \"(size >= 32)\" not met");
   }
   this->size = size;
   return;
}

void Double::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::Metrics::Double::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::Metrics::Double::initialize]: error: guard \"(!initialized)\" not met");
   }
   metrics.reserve(size);
   metrics.resize(size);
   initialized = true;
   head = 0;
   return;
}

void Double::capture(double metric)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::Metrics::Double::capture]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::Metrics::Double::capture]: error: guard \"initialized\" not met");
   }
   head++;
   if (head >= metrics.size()) head = 0;
   metrics[head] = metric;
   return;
}

int Double::head_delta(int delta)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::Metrics::Double::head_delta]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::Metrics::Double::head_delta]: error: guard \"initialized\" not met");
   }
   int pos = head + delta;
   while (pos < 0) pos += metrics.size();
   if (pos >= metrics.size()) pos = pos % metrics.size();
   return pos;
}

double Double::average_of_last_n_metrics(int count)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::Metrics::Double::average_of_last_n_metrics]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::Metrics::Double::average_of_last_n_metrics]: error: guard \"initialized\" not met");
   }
   double sum = 0.0;
   for (int i=0; i<count; i++)
   {
      int index = head_delta(-i);
      sum += metrics[index];
   };
   return sum / count;
}

std::vector<double> Double::get_last_n_metrics(int count)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::Metrics::Double::get_last_n_metrics]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::Metrics::Double::get_last_n_metrics]: error: guard \"initialized\" not met");
   }
   // TODO: Test this
   std::vector<double> result;
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


