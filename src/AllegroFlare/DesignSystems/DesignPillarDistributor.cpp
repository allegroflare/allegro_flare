

#include <AllegroFlare/DesignSystems/DesignPillarDistributor.hpp>




namespace AllegroFlare
{
namespace DesignSystems
{


DesignPillarDistributor::DesignPillarDistributor()
   : design_pillars({})
{
}


DesignPillarDistributor::~DesignPillarDistributor()
{
}


std::vector<AllegroFlare::DesignSystems::DesignPillarDistribution> DesignPillarDistributor::build_distributions()
{
   std::vector<AllegroFlare::DesignSystems::DesignPillarDistribution> result;

   std::vector<std::string> primary_source_list = build_source_list();
   std::vector<std::string> secondary_source_list = build_source_list();
   std::vector<std::string> tertiary_source_list = build_source_list();

   // 1) Number of levels is source_list.size() / 3
   // 2) Each distribution

   return result;
}

std::vector<std::string> DesignPillarDistributor::build_source_list()
{
   std::vector<std::string> result = {
      "Ambience",
      "Action",
      "Friction",
      "Growing Excitement",
      "Cognative Puzzle Solving",
      "Rest",
      "Story",
      "Searching and Discovery (for key)",
      "Aquisition of Wealth/Experience (grinding)",
   };
   return result;
}


} // namespace DesignSystems
} // namespace AllegroFlare


