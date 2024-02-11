
#include <gtest/gtest.h>

#include <AllegroFlare/BacktracingException.hpp>


TEST(AllegroFlare_BacktracingExceptionTest, can_be_created_without_blowing_up)
{
   AllegroFlare::BacktracingException backtracing_exception;
}


TEST(AllegroFlare_BacktracingExceptionTest, when_thrown__will_include_a_backtrace_when_calling_the_what_method)
{
   try
   {
      // Some code that may throw an exception
      throw AllegroFlare::BacktracingException("An error occurred");
   }
   catch (const AllegroFlare::BacktracingException& e)
   //catch (const std::runtime_error& e) // Does not work
   //catch (const std::exception& e) // Does not work
   {
      std::cout << "Caught exception: " << e.what() << std::endl;
   }
}


