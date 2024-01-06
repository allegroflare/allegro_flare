
#include <gtest/gtest.h>

#include <AllegroFlare/Instrumentation/DurationMeasurer.hpp>


TEST(AllegroFlare_Instrumentation_DurationMeasurerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Instrumentation::DurationMeasurer duration_measurer;
}


