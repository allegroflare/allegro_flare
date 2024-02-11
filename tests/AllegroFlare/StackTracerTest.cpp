
#include <gtest/gtest.h>

#include <AllegroFlare/StackTracer.hpp>


TEST(AllegroFlare_StackTracerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::StackTracer stack_tracer;
}


TEST(AllegroFlare_StackTracerTest,
   DISABLED__generate_stack_trace__will_create_a_stack_trace_report_of_the_current_call_stack)
{
   // TODO: Implement this test
   // NOTE: This test works, but will produce different outputs depending on runs.
   // NOTE: This feature currently only works Unix-like systems, and would require implementations
   // for other platforms

   //std::string expected_stack_trace = "foo";
   //std::string actual_stack_trace = AllegroFlare::StackTracer::generate_stack_trace();
   //EXPECT_EQ(expected_stack_trace, actual_stack_trace);
}


