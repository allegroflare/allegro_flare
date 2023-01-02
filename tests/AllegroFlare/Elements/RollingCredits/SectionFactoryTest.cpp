
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/RollingCredits/SectionFactory.hpp>


TEST(AllegroFlare_Elements_RollingCredits_SectionFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::SectionFactory section_factory;
}


TEST(AllegroFlare_Elements_RollingCredits_SectionFactoryTest,
   create_standard_disclaimers_text__returns_text_sections_with_the_expected_disclaimer_text)
{
   // TODO
}


