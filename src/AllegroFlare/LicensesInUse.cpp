

#include <AllegroFlare/LicensesInUse.hpp>




namespace AllegroFlare
{


LicensesInUse::LicensesInUse()
{
}


LicensesInUse::~LicensesInUse()
{
}


std::pair<std::string, std::string> LicensesInUse::generate_exan_font_license()
{
   return {
      "Exan-Regular.ttf",
      "Copyright 2016 by Jon Carlos Morales. All rights reserved."
      // https://fontm.com/exan/
      // https://fontmeme.com/fonts/exan-3-font/
      // https://online-fonts.com/fonts/exan
   };
}

std::pair<std::string, std::string> LicensesInUse::generate_expansiva_font_license()
{
   return {
      "Exan-Regular.ttf",
      // TODO: Load in exact wording of license
      "https://www.1001fonts.com/expansiva-font.html\nhttps://www.1001fonts.com/licenses/ffc.html\n",
      // https://www.1001fonts.com/expansiva-font.html
   };
}


} // namespace AllegroFlare


