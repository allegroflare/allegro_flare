

#include <AllegroFlare/Elements/RollingCredits/Sections/Multicolumn.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{
namespace Sections
{


Multicolumn::Multicolumn(std::vector<std::vector<std::string>> elements)
   : AllegroFlare::Elements::RollingCredits::Sections::Base(AllegroFlare::Elements::RollingCredits::Sections::Multicolumn::TYPE)
   , elements(elements)
{
}


Multicolumn::~Multicolumn()
{
}


void Multicolumn::set_elements(std::vector<std::vector<std::string>> elements)
{
   this->elements = elements;
}


std::vector<std::vector<std::string>> Multicolumn::get_elements() const
{
   return elements;
}


std::vector<std::vector<std::string>> Multicolumn::split_into_columns(std::vector<std::string> names, int num_columns)
{
   if (!((num_columns >= 1)))
   {
      std::stringstream error_message;
      error_message << "[Multicolumn::split_into_columns]: error: guard \"(num_columns >= 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Multicolumn::split_into_columns: error: guard \"(num_columns >= 1)\" not met");
   }
   std::vector<std::vector<std::string>> result;

   std::string default_fill = "";
   int min_items_per_column = (int)names.size() / num_columns;
   int remaining_items_to_distribute = (int)names.size() % num_columns;

   std::cout << "min: " << min_items_per_column << " - remain: " << remaining_items_to_distribute << std::endl;

   // Distribute the known minimum number of elements among the containers
   for (int i=0; i<num_columns; i++) result.push_back(std::vector<std::string>(min_items_per_column, default_fill));

   // Distribute the remainders starting from the left (In the future consider filling center columns first)
   for (int i=0; i<remaining_items_to_distribute; i++) result[i].push_back(default_fill);

   // Fill the containers with the items
   int row_num = 0;
   int column_num = 0;
   for (int i=0; i<names.size(); i++)
   {
      result[column_num][row_num] = names[i];

      row_num++;
      if (row_num >= result[column_num].size())
      {
         column_num++;
         row_num = 0;
      }
   }

   return result;
}


} // namespace Sections
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


