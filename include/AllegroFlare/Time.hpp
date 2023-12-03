#pragma once




namespace AllegroFlare
{
   class Time
   {
   private:
      double absolute_now;
      double playhead;
      double rate;
      double last_rate_changed_at;

   protected:


   public:
      Time();
      ~Time();

      double get_absolute_now() const;
      double get_playhead() const;
      double get_rate() const;
      static double universal_absolute_now();
      void set_absolute_now(double absolute_now=AllegroFlare::Time::universal_absolute_now());
      double now();
      void jump_ahead_sec(double distance=0.0f);
      void set_rate(double rate=1.0f);
      static double calculate_age(double time_now=0.0f, double time_begin=0.0f);
   };
}



