
#include <gtest/gtest.h>

#include <AllegroFlare/Instrumentation/Metrics/TimePoint.hpp>


TEST(AllegroFlare_Instrumentation_Metrics_TimePointTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Instrumentation::Metrics::TimePoint time_point;
}


