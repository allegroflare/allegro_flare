#pragma once


#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


namespace AllegroFlare
{
   namespace Testing
   {
      class WithInteractionFixture : public AllegroFlare::Testing::WithAllegroRenderingFixture
      {
      private:

      protected:


      public:
         WithInteractionFixture();
         virtual ~WithInteractionFixture();

         virtual void SetUp() override;
         virtual void TearDown() override;
      };
   }
}



