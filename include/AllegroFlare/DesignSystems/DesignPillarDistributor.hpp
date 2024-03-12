#pragma once


#include <AllegroFlare/DesignSystems/DesignPillar.hpp>
#include <AllegroFlare/DesignSystems/DesignPillarDistribution.hpp>
#include <vector>


namespace AllegroFlare
{
   namespace DesignSystems
   {
      class DesignPillarDistributor
      {
      private:
         std::vector<AllegroFlare::DesignSystems::DesignPillar> design_pillars;

      protected:


      public:
         DesignPillarDistributor();
         ~DesignPillarDistributor();

         std::vector<AllegroFlare::DesignSystems::DesignPillarDistribution> build_distributions();
      };
   }
}



