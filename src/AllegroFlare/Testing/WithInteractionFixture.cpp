

#include <AllegroFlare/Testing/WithInteractionFixture.hpp>




namespace AllegroFlare
{
namespace Testing
{


WithInteractionFixture::WithInteractionFixture()
   : AllegroFlare::Testing::WithAllegroRenderingFixture()
{
}


WithInteractionFixture::~WithInteractionFixture()
{
}


void WithInteractionFixture::SetUp()
{
   AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();
   return;
}

void WithInteractionFixture::TearDown()
{
   AllegroFlare::Testing::WithAllegroRenderingFixture::TearDown();
   return;
}


} // namespace Testing
} // namespace AllegroFlare


