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
         float event_time;
         int event_type;
         float processing_start_time;
         float processing_end_time;
         int primary_timer_events_dropped;
         PrimaryProcessEventMetric();
         ~PrimaryProcessEventMetric();

         float get_duration();
      };
   }
}



