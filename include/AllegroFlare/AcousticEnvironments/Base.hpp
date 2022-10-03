#pragma once


#include <string>


namespace AllegroFlare
{
   namespace AcousticEnvironments
   {
      class Base
      {
      public:
         static constexpr char* TYPE = "AcousticEnvironments/Base";

      private:
         std::string type;

      protected:


      public:
         Base(std::string type=AllegroFlare::AcousticEnvironments::Base::TYPE);
         ~Base();

         std::string get_type() const;
         bool is_type(std::string possible_type="");
      };
   }
}



