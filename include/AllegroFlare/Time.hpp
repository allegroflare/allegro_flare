#pragma once




namespace AllegroFlare
{
   class Time
   {
   private:
      float started_at;
      float playhead;
      float rate;
      float last_rate_changed_at;

   protected:


   public:
      Time(float started_at=0.0f);
      ~Time();

      void set_started_at(float started_at);
      float get_started_at() const;
      float absolute_now();
      float now();
      void jump_ahead_sec(float distance=0.0f);
      void set_rate(float rate=1.0f);
   };
}



