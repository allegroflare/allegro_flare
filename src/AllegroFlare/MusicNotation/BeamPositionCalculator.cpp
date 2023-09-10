

#include <AllegroFlare/MusicNotation/BeamPositionCalculator.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace MusicNotation
{


BeamPositionCalculator::BeamPositionCalculator(std::vector<std::pair<float, int>> notehead_staff_positions)
   : notehead_staff_positions(notehead_staff_positions)
{
}


BeamPositionCalculator::~BeamPositionCalculator()
{
}


void BeamPositionCalculator::set_notehead_staff_positions(std::vector<std::pair<float, int>> notehead_staff_positions)
{
   this->notehead_staff_positions = notehead_staff_positions;
}


std::vector<std::pair<float, int>> BeamPositionCalculator::get_notehead_staff_positions() const
{
   return notehead_staff_positions;
}


BeamPositionCalculator::StemDirection BeamPositionCalculator::infer_preferred_stem_direction()
{
   if (!(notehead_staff_positions.size() >= 2))
   {
      std::stringstream error_message;
      error_message << "[BeamPositionCalculator::infer_preferred_stem_direction]: error: guard \"notehead_staff_positions.size() >= 2\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BeamPositionCalculator::infer_preferred_stem_direction: error: guard \"notehead_staff_positions.size() >= 2\" not met");
   }
   BeamPositionCalculator::StemDirection result = BeamPositionCalculator::StemDirection::UNDEFINED;

   int min_staff_position = get_min_staff_position();
   int max_staff_position = get_max_staff_position();

   return result;
}

int BeamPositionCalculator::get_first_staff_position()
{
   if (!((!notehead_staff_positions.empty())))
   {
      std::stringstream error_message;
      error_message << "[BeamPositionCalculator::get_first_staff_position]: error: guard \"(!notehead_staff_positions.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BeamPositionCalculator::get_first_staff_position: error: guard \"(!notehead_staff_positions.empty())\" not met");
   }
   return notehead_staff_positions.front().second;
}

int BeamPositionCalculator::get_last_staff_position()
{
   if (!((!notehead_staff_positions.empty())))
   {
      std::stringstream error_message;
      error_message << "[BeamPositionCalculator::get_last_staff_position]: error: guard \"(!notehead_staff_positions.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BeamPositionCalculator::get_last_staff_position: error: guard \"(!notehead_staff_positions.empty())\" not met");
   }
   return notehead_staff_positions.back().second;
}

int BeamPositionCalculator::get_min_staff_position()
{
   int min_value = 0;
   auto min_element = std::min_element(notehead_staff_positions.begin(), notehead_staff_positions.end(), 
      [](const std::pair<float, int>& lhs, const std::pair<float, int>& rhs) {
         return lhs.second < rhs.second;
      });

   if (min_element != notehead_staff_positions.end())
   {
      min_value = min_element->second;
   }
   else
   {
      std::cout << "Vector is empty." << std::endl;
      throw std::runtime_error("BeamPositionCalculator::get_min_staff_position: error: notehead_staff_positions []");
   }
   return min_value;
}

int BeamPositionCalculator::get_max_staff_position()
{
   int min_value = 0;
   auto min_element = std::max_element(notehead_staff_positions.begin(), notehead_staff_positions.end(), 
      [](const std::pair<float, int>& lhs, const std::pair<float, int>& rhs) {
         return lhs.second < rhs.second;
      });

   if (min_element != notehead_staff_positions.end())
   {
      min_value = min_element->second;
   }
   else
   {
      std::cout << "Vector is empty." << std::endl;
      throw std::runtime_error("BeamPositionCalculator::get_max_staff_position: error: notehead_staff_positions []");
   }
   return min_value;
}


} // namespace MusicNotation
} // namespace AllegroFlare


