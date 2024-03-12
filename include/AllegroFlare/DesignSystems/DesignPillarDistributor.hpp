#pragma once


#include <AllegroFlare/DesignSystems/DesignPillar.hpp>
#include <AllegroFlare/DesignSystems/DesignPillarDistribution.hpp>
#include <string>
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
         std::string select_not_of(std::vector<std::string> existing_elements={}, std::vector<std::string> elements_not_to_select={});
         std::vector<std::string> build_source_list();
      };
   }
}



