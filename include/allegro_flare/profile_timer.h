#ifndef __AF_PROFILE_TIMER_HEADER
#define __AF_PROFILE_TIMER_HEADER




// TODO:
// this should be a little more structured.
// for example, a global
// Profiling::start("name");
// but also the possibility of a global
// actually, AllegroFlare should have the profile timer in it, globally.




#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>




typedef char char64_t[64];




#define PROFILE_TIMER_TIME_T double

void start_profile_timer(const char64_t name);
void stop_profile_timer(const char64_t name, PROFILE_TIMER_TIME_T at_time=al_get_time());
PROFILE_TIMER_TIME_T get_profile_timer_length(const char64_t name);
void draw_profile_timer_graph(float x=10, float y=10);




class ProfileTimer
{
public:
   bool timing;
   double start_time;
   double end_time;

   void start()
   {
      timing = true;
      start_time = al_get_time();
   }

   void stop()
   {
      end_time = al_get_time();
      timing = false;
   }

   double get_time()
   {
      if (!timing) return end_time - start_time;
      return 0.0;
   }
};




class ProfilerBuilder
{
private:
   const char *name;
   static ProfilerBuilder *dummy;

public:
   static ProfilerBuilder *get_dummy() { if (!dummy) dummy = new ProfilerBuilder(); return dummy; }
   inline void start() { start_profile_timer(name); }
   inline void stop() { stop_profile_timer(name); }
   inline ProfilerBuilder &clear(const char *name) { this->name = name; return *this; }
};




static inline ProfilerBuilder &profiler(const char *name)
{
   return ProfilerBuilder::get_dummy()->clear(name);
}




#endif
