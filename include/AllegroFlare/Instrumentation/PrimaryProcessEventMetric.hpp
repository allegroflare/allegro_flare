#pragma once




namespace AllegroFlare
{
   namespace Instrumentation
   {
      class PrimaryProcessEventMetric
      {
      private:

      protected:


      public:
         int event_type;
         double event_time;
         double processing_start_time;
         double processing_end_time;
         int primary_timer_events_dropped;
         double al_flip_display_start_time;
         double al_flip_display_end_time;
         PrimaryProcessEventMetric();
         ~PrimaryProcessEventMetric();

         double get_duration();
      };
   }
}



