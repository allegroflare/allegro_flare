

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
   static std::string LICENSE_TEXT = {
      "1001Fonts Free For Commercial Use License (FFC)\n"
      "(captured from https://www.1001fonts.com/licenses/ffc.html)\n\n"

      "Preamble\n"
      "In this license, 'the given typeface' refers to the given .zip file, which may contain "
      "one or numerous fonts. These fonts can be of any type (.ttf, .otf, ...) and together "
      "they form a 'font family' or in short a 'typeface'.\n\n"

      "1. Copyright\n"
      "The given typeface is the intellectual property of its respective author, provided it "
      "is original, and is protected by copyright laws in many parts of the world.\n\n"

      "2. Usage\n"
      "The given typeface may be downloaded and used free of charge for both personal and "
      "commercial use, as long as the usage is not racist or illegal. Personal use refers to "
      "all usage that does not generate financial income in a business manner, for instance:\n"
      "- personal scrapbooking for yourself\n"
      "- recreational websites and blogs for friends and family\n"
      "- prints such as flyers, posters, t-shirts for churches, charities, and non-profit "
      "organizations\n\n"

      "Commercial use refers to usage in a business environment, including:\n"
      "- business cards, logos, advertising, websites, mobile apps for companies\n"
      "- t-shirts, books, apparel that will be sold for money\n"
      "- flyers, posters for events that charge admission\n"
      "- freelance graphic design work\n"
      "- anything that will generate direct or indirect income\n\n"

      "3. Modification\n"
      "The given typeface may not be modified, altered, adapted or built upon without written "
      "permission by its respective author. This pertains to all files within the downloadable "
      "font zip-file.\n\n"

      "4. Conversion\n"
      "The given typeface may be converted to other formats such as WOFF, SVG or EOT webfonts, "
      "as long as the font is not modified in any other way, such as changing names or altering "
      "individual glyphs.\n\n"

      "5. Distribution\n"
      "While the given typeface may freely be copied and passed along to other individuals for "
      "private use as its original downloadable zip-file, it may not be sold or published without "
      "written permission by its respective author.\n\n"

      "6. Embedding\n"
      "The given typeface may be embedded into an application such as a web- or mobile app, "
      "independent of the number of the application users, as long as the application does not "
      "distribute the given typeface, such as offering it as a download.\n\n"

      "7. Disclaimer\n"
      "The given typeface is offered 'as is' without any warranty. 1001fonts.com and the "
      "respective author of the given typeface shall not be liable for any damage derived from "
      "using this typeface. By using the given typeface you agree to the terms of this license.\n"
   };

   // TODO: Validate the contents of the text string with the content of the website. Note the text above
   // was formatted by AI and should be double-checked for mistakes.

   return {
      "Exan-Regular.ttf",
      LICENSE_TEXT

      // TODO: Include the following links for this specific resource:

      // https://www.1001fonts.com/expansiva-font.html
      // https://www.1001fonts.com/licenses/ffc.html
   };
}


} // namespace AllegroFlare


