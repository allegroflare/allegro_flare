

#include <AllegroFlare/Instrumentation/Metric.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Instrumentation
{


Metric::Metric()
   : metrics(false)
   , size(64*4)
   , head(0)
   , initialized(false)
{
}


Metric::~Metric()
{
}


int Metric::get_size() const
{
   return size;
}


int Metric::get_head() const
{
   return head;
}


std::vector<double> &Metric::get_metrics_ref()
{
   return metrics;
}


void Metric::set_size(int size)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Metric::set_size]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Metric::set_size: error: guard \"(!initialized)\" not met");
   }
   if (!((size >= 32)))
   {
      std::stringstream error_message;
      error_message << "[Metric::set_size]: error: guard \"(size >= 32)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Metric::set_size: error: guard \"(size >= 32)\" not met");
   }
   this->size = size;
   return;
}

void Metric::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Metric::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Metric::initialize: error: guard \"(!initialized)\" not met");
   }
   metrics.reserve(size);
   metrics.resize(size);
   initialized = true;
   head = 0;
   return;
}

void Metric::capture(double metric)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Metric::capture]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Metric::capture: error: guard \"initialized\" not met");
   }
   head++;
   if (head >= metrics.size()) head = 0;
   metrics[head] = metric;
   return;
}

int Metric::head_delta(int delta)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Metric::head_delta]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Metric::head_delta: error: guard \"initialized\" not met");
   }
   int pos = head + delta;
   while (pos < 0) pos += metrics.size();
   if (pos >= metrics.size()) pos = pos % metrics.size();
   return pos;
}

double Metric::average_of_last_n_metrics(int count)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Metric::average_of_last_n_metrics]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Metric::average_of_last_n_metrics: error: guard \"initialized\" not met");
   }
   double sum = 0.0;
   for (int i=0; i<count; i++)
   {
      int index = head_delta(-i);
      sum += metrics[index];
   };
   return sum / count;
}

std::vector<double> Metric::get_last_n_metrics(int count)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Metric::get_last_n_metrics]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Metric::get_last_n_metrics: error: guard \"initialized\" not met");
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


} // namespace Instrumentation
} // namespace AllegroFlare


