
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Text.hpp>


TEST(AllegroFlare_Elements_RollingCredits_SectionRenderers_TextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Text text;
}


TEST(AllegroFlare_Elements_RollingCredits_SectionRenderers_TextTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Text text;
   EXPECT_EQ("SectionRenderers/Text", text.get_type());
}


TEST(AllegroFlare_Elements_RollingCredits_SectionRenderers_TextTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Text text;
   EXPECT_EQ(AllegroFlare::Elements::RollingCredits::SectionRenderers::Text::TYPE, text.get_type());
}


