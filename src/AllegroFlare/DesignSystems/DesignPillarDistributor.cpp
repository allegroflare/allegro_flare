

#include <AllegroFlare/DesignSystems/DesignPillarDistributor.hpp>

#include <AllegroFlare/Random.hpp>
#include <iostream>


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


std::vector<AllegroFlare::DesignSystems::DesignFocus> DesignPillarDistributor::build_distribution()
{
   std::vector<AllegroFlare::DesignSystems::DesignFocus> result;

   std::vector<std::string> source_list = build_source_list();
   int num_elements = source_list.size();

   // Build our containers
   std::vector<std::string> primary_source_list = source_list;
   std::vector<std::string> secondary_source_list = source_list;
   std::vector<std::string> tertiary_source_list = source_list;

   // 1) Shuffle all lists
   AllegroFlare::Random random;
   random.set_seed(157618);
   random.shuffle_elements(primary_source_list);
   random.shuffle_elements(secondary_source_list);
   random.shuffle_elements(tertiary_source_list);

   int i = 0;
   while (!primary_source_list.empty())
   {
      // 2) Pop from first
      std::string primary_element = primary_source_list.back();
      primary_source_list.pop_back();
      i++;

      // 3a) Select from second
      std::string secondary_element = select_not_of(secondary_source_list, { primary_element });
      // 3b) Remove selected element from second
      secondary_source_list = remove_element(secondary_source_list, secondary_element);
      // 3a) Select from third
      std::string tertiary_element = select_not_of(tertiary_source_list, { primary_element, secondary_element });
      // 3b) Remove selected element from third
      tertiary_source_list = remove_element(tertiary_source_list, tertiary_element);

      // NOTE: Number of levels is source_list.size() / 3

      // Output a little report
      std::cout << "- Selection " << i << std::endl;
      std::cout << "  - primary: " << primary_element << std::endl;
      std::cout << "    secondary: " << secondary_element << std::endl;
      std::cout << "    tertiary: " << tertiary_element << std::endl;
   }

   return result;
}

std::string DesignPillarDistributor::select_not_of(std::vector<std::string> existing_elements, std::vector<std::string> elements_not_to_select)
{
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

std::vector<std::string> DesignPillarDistributor::remove_element(std::vector<std::string> elements, std::string element_to_remove)
{
   elements.erase(
         std::remove(elements.begin(), elements.end(), element_to_remove), elements.end()
      );
   return elements;
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


