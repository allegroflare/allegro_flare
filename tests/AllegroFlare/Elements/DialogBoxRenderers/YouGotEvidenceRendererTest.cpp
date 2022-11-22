
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxRenderers/YouGotEvidenceRenderer.hpp>


TEST(AllegroFlare_Elements_DialogBoxRenderers_YouGotEvidenceRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::YouGotEvidenceRenderer you_got_evidence_renderer;
}


TEST(AllegroFlare_Elements_DialogBoxRenderers_YouGotEvidenceRendererTest, run__returns_the_expected_response)
{
   AllegroFlare::Elements::DialogBoxRenderers::YouGotEvidenceRenderer you_got_evidence_renderer;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, you_got_evidence_renderer.run());
}


