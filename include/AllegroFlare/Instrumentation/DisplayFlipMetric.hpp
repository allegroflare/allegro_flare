#pragma once




namespace AllegroFlare
{
   namespace Instrumentation
   {
      class DisplayFlipMetric
      {
      private:

      protected:


      public:
         double start_time;
         double end_time;
         DisplayFlipMetric();
         ~DisplayFlipMetric();

         double get_duration();
      };
   }
}



