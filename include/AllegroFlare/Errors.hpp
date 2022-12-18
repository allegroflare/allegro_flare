#pragma once


#include <string>


namespace AllegroFlare
{
   class Errors
   {
   private:

   protected:


   public:
      Errors();
      ~Errors();

      static std::string build_error_message(std::string from="[unset-from]", std::string message="[unset-message]");
      static void throw_error(std::string from="[unset-from]", std::string message="[unset-message]");
   };
}



