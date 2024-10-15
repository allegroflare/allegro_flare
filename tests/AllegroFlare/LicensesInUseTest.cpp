
#include <gtest/gtest.h>

#include <AllegroFlare/LicensesInUse.hpp>


TEST(AllegroFlare_LicensesInUseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::LicensesInUse licenses_in_use;
}


TEST(AllegroFlare_LicensesInUseTest, generate_expansiva_font_license__contains_the_expected_license_text)
{
   // TODO: Test generate_expansiva_font_license and test against a hash or literal text to ensure it remains
   // unmodified.
   AllegroFlare::LicensesInUse licenses_in_use;
}


