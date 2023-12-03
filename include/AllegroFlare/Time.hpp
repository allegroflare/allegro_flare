#pragma once




namespace AllegroFlare
{
   class Time
   {
   private:
      double started_at;
      double playhead;
      double rate;
      double last_rate_changed_at;

   protected:


   public:
      Time(double started_at=0.0);
      ~Time();

      void set_started_at(double started_at);
      double get_started_at() const;
      double get_rate() const;
      static double universal_absolute_now();
      double now(double time_now=AllegroFlare::Time::universal_absolute_now());
      void jump_ahead_sec(double distance=0.0f);
      void set_rate(double rate=1.0f, double time_now=AllegroFlare::Time::universal_absolute_now());
      static double calculate_age(double time_now=0.0f, double time_begin=0.0f);
   };
}



