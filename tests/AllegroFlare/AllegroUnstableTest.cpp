
#include <gtest/gtest.h>



TEST(AllegroFlare_AllegroUnstable, ALLEGRO_UNSTABLE_is_not_defined) {
    // Check if the macro is defined
#ifdef ALLEGRO_UNSTABLE
    ASSERT_TRUE(false) << "ALLEGRO_UNSTABLE is already defined";
#else
    ASSERT_TRUE(true);
#endif
}


#include <AllegroFlare/AllegroUnstable.hpp>


TEST(AllegroFlare_AllegroUnstable, defines_ALLEGRO_UNSTABLE) {
    // Check if the macro is defined
#ifdef ALLEGRO_UNSTABLE
    ASSERT_TRUE(true);  // If defined, the test will pass
#else
    ASSERT_TRUE(false) << "ALLEGRO_UNSTABLE is not defined";
#endif
}


