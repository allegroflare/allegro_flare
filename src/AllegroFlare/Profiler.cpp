

#include <AllegroFlare/Profiler.hpp>

#include <iostream>
#include <sstream>
#include <algorithm>


namespace AllegroFlare
{


Profiler::Profiler()
   : timers()
{}


Profiler::~Profiler()
{
}


AllegroFlare::Timer *Profiler::find_or_create(std::string name)
{
   std::map<std::string, AllegroFlare::Timer>::iterator it = timers.find(name);
   if (it == timers.end())
   {
      timers[name] = AllegroFlare::Timer();
      return &timers[name];
   }
   return &it->second;
}


std::map<std::string, AllegroFlare::Timer> Profiler::get_timers()
{
   return this->timers;
}


std::map<std::string, AllegroFlare::Timer> &Profiler::get_timers_ref()
{
   return this->timers;
}


std::map<std::string, std::vector<std::chrono::high_resolution_clock::time_point>> Profiler::get_event_buckets()
{
   return this->event_buckets;
}


std::list<std::string> Profiler::get_event_bucket_names()
{
   std::list<std::string> result;
   for (auto &event_bucket : event_buckets)
   {
      result.push_back(event_bucket.first);
   }
   return result;
}


int Profiler::get_event_bucket_num_samples(std::string event_bucket_name)
{
   if (event_buckets.find(event_bucket_name) == event_buckets.end()) return 0;
   return event_buckets[event_bucket_name].size();
}


int Profiler::get_event_bucket_duration_between_last_two_samples(std::string event_bucket_name)
{
   if (event_buckets.find(event_bucket_name) == event_buckets.end()) return 0;

   std::vector<std::chrono::high_resolution_clock::time_point> &bucket = event_buckets[event_bucket_name];
   if (bucket.size() <= 1) return 0;

   std::chrono::high_resolution_clock::time_point &most_recent_event_time = bucket[bucket.size() - 1];
   std::chrono::high_resolution_clock::time_point &second_most_recent_event_time = bucket[bucket.size() - 2];

   return std::chrono::duration_cast<std::chrono::microseconds>(
         most_recent_event_time - second_most_recent_event_time
      ).count();
}


void Profiler::start(std::string name)
{
   find_or_create(name)->start();
}


void Profiler::pause(std::string name)
{
   find_or_create(name)->pause();
}


void Profiler::stop(std::string name)
{
   find_or_create(name)->stop();
}


void Profiler::reset(std::string name)
{
   find_or_create(name)->reset();
}


void Profiler::emit(std::string name)
{
   std::chrono::high_resolution_clock::time_point event_time = std::chrono::high_resolution_clock::now();
   event_buckets[name].push_back(event_time);
}


std::vector<std::chrono::high_resolution_clock::time_point> Profiler::get_event_samples(
      std::string name,
      int max_samples
   )
{
   std::vector<std::chrono::high_resolution_clock::time_point> &events_for_this_bucket = event_buckets[name];
   if (max_samples < 0) max_samples = 0;
   if (max_samples > events_for_this_bucket.size()) max_samples = events_for_this_bucket.size();

   std::vector<std::chrono::high_resolution_clock::time_point> events_to_return
      (events_for_this_bucket.end() - max_samples, events_for_this_bucket.end());
   return events_to_return;
}


void Profiler::clear()
{
   timers.clear();
   event_buckets.clear();
}


} // AllegroFlare



