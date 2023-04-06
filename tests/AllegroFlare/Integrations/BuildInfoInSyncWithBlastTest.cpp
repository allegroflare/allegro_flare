
#include <gtest/gtest.h>

#include <AllegroFlare/Integrations/BuildInfoInSyncWithBlast.hpp>
#include <AllegroFlare/UsefulPHP.hpp>


TEST(AllegroFlare_Integrations_BuildInfoInSyncWithBlastTest, run__returns_the_expected_response)
{
   std::string blast_expected_generated_BuildInfo_hpp_filename =
      "/Users/markoates/Repos/blast/tests/fixtures/BuildInfo_hpp_file_content.txt";
   std::string allegro_flare_generated_BuildInfo_hpp_filename =
      "/Users/markoates/Repos/allegro_flare/include/BuildInfo.hpp";

   std::string blast_file_contents = AllegroFlare::php::file_get_contents(
      blast_expected_generated_BuildInfo_hpp_filename
   );
   std::string allegro_flare_file_contents = AllegroFlare::php::file_get_contents(
      allegro_flare_generated_BuildInfo_hpp_filename
   );

   EXPECT_EQ(blast_file_contents, allegro_flare_file_contents);
}


