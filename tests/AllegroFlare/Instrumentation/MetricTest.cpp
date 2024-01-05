
#include <gtest/gtest.h>

#include <AllegroFlare/Instrumentation/Metric.hpp>


TEST(AllegroFlare_Instrumentation_MetricTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Instrumentation::Metric metric;
}


TEST(AllegroFlare_Instrumentation_MetricTest, size__contains_the_expected_default_value)
{
   AllegroFlare::Instrumentation::Metric metric;
   EXPECT_EQ(64*4, metric.get_size());
}


TEST(AllegroFlare_Instrumentation_MetricTest, initialize__will_set_the_size_of_the_metrics_to_the_size)
{
   AllegroFlare::Instrumentation::Metric metric;
   metric.initialize();
   std::vector<double> &metrics = metric.get_metrics_ref();
   EXPECT_EQ(metric.get_size(), metrics.size());
}


TEST(AllegroFlare_Instrumentation_MetricTest, capture__will_move_the_head_forward)
{
   AllegroFlare::Instrumentation::Metric metric;
   metric.initialize();

   EXPECT_EQ(0, metric.get_head());
   metric.capture(0.2);
   EXPECT_EQ(1, metric.get_head());
}


TEST(AllegroFlare_Instrumentation_MetricTest, capture__will_store_the_metric_at_the_head)
{
   AllegroFlare::Instrumentation::Metric metric;
   metric.initialize();

   std::vector<double> &metrics = metric.get_metrics_ref();
   metric.capture(0.2);
   EXPECT_EQ(0.2, metrics[metric.get_head()]);
}


TEST(AllegroFlare_Instrumentation_MetricTest, average_of_last_n_metrics__will_return_the_average)
{
   AllegroFlare::Instrumentation::Metric metric;
   metric.initialize();

   metric.capture(0.2);
   metric.capture(0.4);
   metric.capture(0.6);
   metric.capture(0.8);
   metric.capture(1.0);
   EXPECT_FLOAT_EQ(0.6, metric.average_of_last_n_metrics(5));
}


