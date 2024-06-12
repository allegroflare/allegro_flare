

#include <AllegroFlare/Instrumentation/DurationMeasurer.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Instrumentation
{


DurationMeasurer::DurationMeasurer()
   : metrics(false)
   , size(64*4)
   , head(0)
   , initial_time_measurement(std::chrono::steady_clock::time_point())
   , is_measuring(false)
   , initialized(false)
{
}


DurationMeasurer::~DurationMeasurer()
{
}


int DurationMeasurer::get_size() const
{
   return size;
}


int DurationMeasurer::get_head() const
{
   return head;
}


std::vector<double> &DurationMeasurer::get_metrics_ref()
{
   return metrics;
}


void DurationMeasurer::set_size(int size)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::DurationMeasurer::set_size]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::DurationMeasurer::set_size]: error: guard \"(!initialized)\" not met");
   }
   if (!((size >= 32)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::DurationMeasurer::set_size]: error: guard \"(size >= 32)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::DurationMeasurer::set_size]: error: guard \"(size >= 32)\" not met");
   }
   this->size = size;
   return;
}

void DurationMeasurer::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::DurationMeasurer::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::DurationMeasurer::initialize]: error: guard \"(!initialized)\" not met");
   }
   metrics.reserve(size);
   metrics.resize(size);
   initialized = true;
   head = 0;
   return;
}

void DurationMeasurer::start_capture()
{
   if (!((!is_measuring)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::DurationMeasurer::start_capture]: error: guard \"(!is_measuring)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::DurationMeasurer::start_capture]: error: guard \"(!is_measuring)\" not met");
   }
   initial_time_measurement = std::chrono::steady_clock::now();
   is_measuring = true;
   return;
}

void DurationMeasurer::end_capture()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::DurationMeasurer::end_capture]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::DurationMeasurer::end_capture]: error: guard \"initialized\" not met");
   }
   if (!(is_measuring))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::DurationMeasurer::end_capture]: error: guard \"is_measuring\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::DurationMeasurer::end_capture]: error: guard \"is_measuring\" not met");
   }
   std::chrono::steady_clock::time_point time_point_end = std::chrono::steady_clock::now();
   //initial_time_measurement = std::chrono::steady_clock::now();
   double metric = std::chrono::duration_cast<std::chrono::microseconds>(
                  time_point_end - initial_time_measurement
               ).count()
          / 1'000'000.0; // Convert to seconds
   head++;
   if (head >= metrics.size()) head = 0;
   metrics[head] = metric;
   is_measuring = false;
   return;
}

int DurationMeasurer::head_delta(int delta)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::DurationMeasurer::head_delta]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::DurationMeasurer::head_delta]: error: guard \"initialized\" not met");
   }
   int pos = head + delta;
   while (pos < 0) pos += metrics.size();
   if (pos >= metrics.size()) pos = pos % metrics.size();
   return pos;
}

double DurationMeasurer::average_of_last_n_metrics(int count)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::DurationMeasurer::average_of_last_n_metrics]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::DurationMeasurer::average_of_last_n_metrics]: error: guard \"initialized\" not met");
   }
   double sum = 0.0;
   for (int i=0; i<count; i++)
   {
      int index = head_delta(-i);
      sum += metrics[index];
   };
   return sum / count;
}

std::vector<double> DurationMeasurer::get_last_n_metrics(int count)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::DurationMeasurer::get_last_n_metrics]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::DurationMeasurer::get_last_n_metrics]: error: guard \"initialized\" not met");
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

double DurationMeasurer::get_last_metric()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Instrumentation::DurationMeasurer::get_last_metric]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Instrumentation::DurationMeasurer::get_last_metric]: error: guard \"initialized\" not met");
   }
   // TODO: Test this
   return metrics[head];
}


} // namespace Instrumentation
} // namespace AllegroFlare


