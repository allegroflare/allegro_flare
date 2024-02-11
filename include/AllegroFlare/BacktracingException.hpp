#pragma once


#include <stdexcept>
#include <string>


namespace AllegroFlare
{
   class BacktracingException : public std::runtime_error
   {
   private:
      std::string message;

   protected:


   public:
      BacktracingException(std::string message="[unset-message]");
      ~BacktracingException();

      std::string generate_stack_trace();
   };
}



