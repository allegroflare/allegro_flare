

#include <AllegroFlare/FlipSync.hpp>

#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


FlipSync::FlipSync()
   : currently_capturing_flip_sync(false)
   , flip_metrics(false)
   , size(64*4)
   , head(0)
   , initialized(false)
{
}


FlipSync::~FlipSync()
{
}


int FlipSync::get_size() const
{
   return size;
}


void FlipSync::set_size(int size)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[FlipSync::set_size]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FlipSync::set_size: error: guard \"(!initialized)\" not met");
   }
   if (!((size >= 32)))
   {
      std::stringstream error_message;
      error_message << "[FlipSync::set_size]: error: guard \"(size >= 32)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FlipSync::set_size: error: guard \"(size >= 32)\" not met");
   }
   this->size = size;
   return;
}

void FlipSync::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[FlipSync::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FlipSync::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[FlipSync::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FlipSync::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   //std::size_t size = 64*4; // At 60fps, 64*4 is roughly 4 seconds of frame time metrics, and a good size
   flip_metrics.reserve(size);
   flip_metrics.resize(size);
   initialized = true;
   head = 0;
   return;
}

void FlipSync::start_flip_capture()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[FlipSync::start_flip_capture]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FlipSync::start_flip_capture: error: guard \"initialized\" not met");
   }
   if (!((!currently_capturing_flip_sync)))
   {
      std::stringstream error_message;
      error_message << "[FlipSync::start_flip_capture]: error: guard \"(!currently_capturing_flip_sync)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FlipSync::start_flip_capture: error: guard \"(!currently_capturing_flip_sync)\" not met");
   }
   double time_now = al_get_time();
   flip_metrics[head].first = time_now;
   currently_capturing_flip_sync = true;
   return;
}

void FlipSync::end_flip_capture()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[FlipSync::end_flip_capture]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FlipSync::end_flip_capture: error: guard \"initialized\" not met");
   }
   if (!(currently_capturing_flip_sync))
   {
      std::stringstream error_message;
      error_message << "[FlipSync::end_flip_capture]: error: guard \"currently_capturing_flip_sync\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FlipSync::end_flip_capture: error: guard \"currently_capturing_flip_sync\" not met");
   }
   double time_now = al_get_time();
   flip_metrics[head].second = time_now;
   head++;
   if (head >= flip_metrics.size()) head = 0;
   currently_capturing_flip_sync = false;
   return;
}

int FlipSync::head_delta(int delta)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[FlipSync::head_delta]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FlipSync::head_delta: error: guard \"initialized\" not met");
   }
   int pos = head + delta;
   while (pos < 0) pos += flip_metrics.size();
   if (pos >= flip_metrics.size()) pos = pos % flip_metrics.size();
   return pos;
}

std::vector<double> FlipSync::get_last_n_capture_durations(int count)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[FlipSync::get_last_n_capture_durations]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FlipSync::get_last_n_capture_durations: error: guard \"initialized\" not met");
   }
   // TODO: Test this
   std::vector<double> result;
   result.resize(count);
   for (int i=0; i<result.size(); i++)
   {
      int index = head_delta(-i);
      result[i] = flip_metrics[index].second - flip_metrics[index].first;
   };
   return result;
}


} // namespace AllegroFlare


