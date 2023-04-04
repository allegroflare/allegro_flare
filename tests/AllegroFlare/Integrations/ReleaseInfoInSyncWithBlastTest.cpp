
#include <gtest/gtest.h>

#include <AllegroFlare/Integrations/ReleaseInfoInSyncWithBlast.hpp>
#include <AllegroFlare/UsefulPHP.hpp>


TEST(AllegroFlare_Integrations_ReleaseInfoInSyncWithBlastTest, run__returns_the_expected_response)
{
   std::string blast_expected_generated_ReleaseInfo_hpp_filename =
      "/Users/markoates/Repos/blast/tests/fixtures/ReleaseInfo_hpp_file_content.txt";
   std::string allegro_flare_generated_ReleaseInfo_hpp_filename =
      "/Users/markoates/Repos/allegro_flare/include/ReleaseInfo.hpp";

   std::string blast_file_contents = AllegroFlare::php::file_get_contents(
      blast_expected_generated_ReleaseInfo_hpp_filename
   );
   std::string allegro_flare_file_contents = AllegroFlare::php::file_get_contents(
      allegro_flare_generated_ReleaseInfo_hpp_filename
   );

   EXPECT_EQ(blast_file_contents, allegro_flare_file_contents);
}


