
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/Platforming2D/MapDictionaryListing.hpp>


TEST(AllegroFlare_Prototypes_Platforming2D_MapDictionaryListingTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::MapDictionaryListing map_dictionary_listing;
}


TEST(AllegroFlare_Prototypes_Platforming2D_MapDictionaryListingTest, run__returns_the_expected_response)
{
   AllegroFlare::Prototypes::Platforming2D::MapDictionaryListing map_dictionary_listing;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, map_dictionary_listing.run());
}


