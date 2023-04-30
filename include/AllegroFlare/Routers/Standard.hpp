#pragma once


#include <AllegroFlare/Routers/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Routers
   {
      class Standard : public AllegroFlare::Routers::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Routers/Standard";

      private:
         std::string property;

      protected:


      public:
         Standard(std::string property="[unset-property]");
         ~Standard();

         std::string get_property() const;
         bool property_is(std::string possible_type="");
      };
   }
}



