#pragma once


#include <AllegroFlare/DesignSystems/DesignFocus.hpp>
#include <AllegroFlare/DesignSystems/DesignPillar.hpp>
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

         std::vector<AllegroFlare::DesignSystems::DesignFocus> build_distribution(int seed=157618);
         std::string select_not_of(std::vector<std::string> existing_elements={}, std::vector<std::string> elements_not_to_select={});
         std::vector<std::string> remove_element(std::vector<std::string> elements={}, std::string element_to_remove="[unset-element]");
         std::vector<std::string> build_source_list();
      };
   }
}



