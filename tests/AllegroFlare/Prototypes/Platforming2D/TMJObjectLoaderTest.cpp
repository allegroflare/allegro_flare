
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/Platforming2D/TMJObjectLoader.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


TEST(AllegroFlare_Prototypes_Platforming2D_TMJObjectLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::TMJObjectLoader tmjobject_loader;
}


TEST(AllegroFlare_Prototypes_Platforming2D_TMJObjectLoaderTest, load__on_a_file_that_does_not_exist__throws_an_error)
{
   std::string filename = "some-file-that-does-not-exist.tmj";
   AllegroFlare::Prototypes::Platforming2D::TMJObjectLoader loader(filename);

   std::string expected_error_message = "[KrampusReturns::TMJObjectLoader::load()]: error: The file \""
                                        + filename + "\" does not exist.";

   ASSERT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


