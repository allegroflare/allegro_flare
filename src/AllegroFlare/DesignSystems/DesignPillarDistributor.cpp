

#include <AllegroFlare/DesignSystems/DesignPillarDistributor.hpp>

#include <AllegroFlare/Random.hpp>


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

   // 1) Shuffle all lists
   AllegroFlare::Random random;
   random.set_seed(157618);
   random.shuffle_elements(primary_source_list);
   random.shuffle_elements(secondary_source_list);
   random.shuffle_elements(tertiary_source_list);

   // 2) Pop from first
   // 3a) Select from second
   // 3b) Remove selected element from second
   // 3a) Select from third
   // 3b) Remove selected element from third

   // NOTE: Number of levels is source_list.size() / 3

   return result;
}

std::string DesignPillarDistributor::select_not_of(std::vector<std::string> existing_elements, std::vector<std::string> elements_not_to_select)
{
   //std::string getRandomElement(const std::vector<std::string>& shuffledList, const std::vector<std::string>& elementsNotToSelect) {
   for (const std::string& element : existing_elements)
   {
      if (std::find(elements_not_to_select.begin(), elements_not_to_select.end(), element) == elements_not_to_select.end())
      {
         return element; // Found an element not in elements_not_to_select
      }
   }

   throw std::runtime_error("select_not_of couldn't locate an element");
   // Handle the case when all elements are in elements_not_to_select
   return ""; // or throw an exception, depending on your requirements
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


