#pragma once


#include <AllegroFlare/DesignSystems/DesignPillar.hpp>


namespace AllegroFlare
{
   namespace DesignSystems
   {
      class DesignPillarDistribution
      {
      private:

      protected:


      public:
         AllegroFlare::DesignSystems::DesignPillar primary;
         AllegroFlare::DesignSystems::DesignPillar secondary;
         AllegroFlare::DesignSystems::DesignPillar tertiary;
         DesignPillarDistribution();
         ~DesignPillarDistribution();

      };
   }
}



