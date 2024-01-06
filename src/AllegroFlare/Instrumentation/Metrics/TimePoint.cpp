

#include <AllegroFlare/Instrumentation/Metrics/TimePoint.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Instrumentation
{
namespace Metrics
{


TimePoint::TimePoint()
   : metrics(false)
   , size(64*4)
   , head(0)
   , initialized(false)
{
}


TimePoint::~TimePoint()
{
}


int TimePoint::get_size() const
{
   return size;
}


int TimePoint::get_head() const
{
   return head;
}


std::vector<std::chrono::steady_clock::time_point> &TimePoint::get_metrics_ref()
{
   return metrics;
}


void TimePoint::set_size(int size)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[TimePoint::set_size]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TimePoint::set_size: error: guard \"(!initialized)\" not met");
   }
   if (!((size >= 32)))
   {
      std::stringstream error_message;
      error_message << "[TimePoint::set_size]: error: guard \"(size >= 32)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TimePoint::set_size: error: guard \"(size >= 32)\" not met");
   }
   this->size = size;
   return;
}

void TimePoint::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[TimePoint::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TimePoint::initialize: error: guard \"(!initialized)\" not met");
   }
   metrics.reserve(size);
   metrics.resize(size);
   initialized = true;
   head = 0;
   return;
}

void TimePoint::capture(std::chrono::steady_clock::time_point metric)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TimePoint::capture]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TimePoint::capture: error: guard \"initialized\" not met");
   }
   head++;
   if (head >= metrics.size()) head = 0;
   metrics[head] = metric;
   return;
}

int TimePoint::head_delta(int delta)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TimePoint::head_delta]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TimePoint::head_delta: error: guard \"initialized\" not met");
   }
   int pos = head + delta;
   while (pos < 0) pos += metrics.size();
   if (pos >= metrics.size()) pos = pos % metrics.size();
   return pos;
}

std::vector<std::chrono::steady_clock::time_point> TimePoint::get_last_n_metrics(int count)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TimePoint::get_last_n_metrics]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TimePoint::get_last_n_metrics: error: guard \"initialized\" not met");
   }
   // TODO: Test this
   std::vector<std::chrono::steady_clock::time_point> result;
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


