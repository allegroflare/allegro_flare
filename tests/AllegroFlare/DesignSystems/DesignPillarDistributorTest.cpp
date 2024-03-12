
#include <gtest/gtest.h>

#include <AllegroFlare/DesignSystems/DesignPillarDistributor.hpp>


TEST(AllegroFlare_DesignSystems_DesignPillarDistributorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DesignSystems::DesignPillarDistributor design_pillar_distributor;
}


TEST(AllegroFlare_DesignSystems_DesignPillarDistributorTest,
   build_distribution__will_distribute_the_design_pillars_in_the_expected_way)
{
   AllegroFlare::DesignSystems::DesignPillarDistributor design_pillar_distributor;

   std::vector<AllegroFlare::DesignSystems::DesignFocus> distribution =
      design_pillar_distributor.build_distribution();
}


