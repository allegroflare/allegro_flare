#pragma once


#include <AllegroFlare/AcousticEnvironments/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace AcousticEnvironments
   {
      class Reverb : public AllegroFlare::AcousticEnvironments::Base
      {
      public:
         static constexpr char* TYPE = "AcousticEnvironments/Reverb";

      private:
         std::string property;

      protected:


      public:
         Reverb(std::string property="[unset-property]");
         ~Reverb();

         std::string get_property() const;
         bool property_is(std::string possible_type="");
      };
   }
}



