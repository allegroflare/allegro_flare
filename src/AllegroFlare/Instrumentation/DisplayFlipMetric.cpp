

#include <AllegroFlare/Instrumentation/DisplayFlipMetric.hpp>




namespace AllegroFlare
{
namespace Instrumentation
{


DisplayFlipMetric::DisplayFlipMetric()
   : start_time(0)
   , end_time(0)
{
}


DisplayFlipMetric::~DisplayFlipMetric()
{
}


double DisplayFlipMetric::get_duration()
{
   return end_time - start_time;
}


} // namespace Instrumentation
} // namespace AllegroFlare


