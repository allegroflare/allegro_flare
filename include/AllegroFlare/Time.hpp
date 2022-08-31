#pragma once




namespace AllegroFlare
{
   class Time
   {
   private:
      float started_at;

   protected:


   public:
      Time(float started_at=0.0f);
      ~Time();

      void set_started_at(float started_at);
      float get_started_at() const;
      float now();
   };
}



