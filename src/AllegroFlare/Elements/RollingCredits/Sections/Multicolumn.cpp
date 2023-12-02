

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
   std::vector<std::vector<std::string>> result; //(num_rows, std::vector<std::string>(num_columns, ""));

   int items_per_column = static_cast<int>(std::ceil(static_cast<double>(names.size()) / num_columns));

   //std::cout << 

   int item_count_in_this_column = 0;
   std::vector<std::string> column;
   int i=0;
   for (i=0; i<(int)names.size(); ++i)
   {
      column.push_back(names[i]);
      item_count_in_this_column++;

      if (item_count_in_this_column >= items_per_column)
      {
         item_count_in_this_column = 0;
         result.push_back(column);
         column.clear();
      }
   }

   // Append the last column if it is incomplete
   if (!column.empty()) result.push_back(column);

   return result;
}


} // namespace Sections
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


