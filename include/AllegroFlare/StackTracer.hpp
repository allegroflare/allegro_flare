#pragma once


#include <string>


namespace AllegroFlare
{
   class StackTracer
   {
   private:

   protected:


   public:
      StackTracer();
      ~StackTracer();

      static std::string generate_stack_trace();
   };
}



