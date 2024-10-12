#pragma once


#include <string>
#include <utility>


namespace AllegroFlare
{
   class LicensesInUse
   {
   private:

   protected:


   public:
      LicensesInUse();
      ~LicensesInUse();

      std::pair<std::string, std::string> generate_exan_font_license();
      std::pair<std::string, std::string> generate_expansiva_font_license();
   };
}



