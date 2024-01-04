

#include <AllegroFlare/Instrumentation/PrimaryProcessEventMetric.hpp>




namespace AllegroFlare
{
namespace Instrumentation
{


PrimaryProcessEventMetric::PrimaryProcessEventMetric()
   : event_type(0)
   , event_time(0.0)
   , processing_start_time(0)
   , processing_end_time(0)
   , primary_timer_events_dropped(0)
   , al_flip_display_start_time(0)
   , al_flip_display_end_time(0)
{
}


PrimaryProcessEventMetric::~PrimaryProcessEventMetric()
{
}


double PrimaryProcessEventMetric::get_duration()
{
   return processing_end_time - processing_start_time;
}


} // namespace Instrumentation
} // namespace AllegroFlare


