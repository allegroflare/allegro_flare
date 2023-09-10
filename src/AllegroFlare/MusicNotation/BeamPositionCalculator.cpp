

#include <AllegroFlare/MusicNotation/BeamPositionCalculator.hpp>




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
   BeamPositionCalculator::StemDirection result = BeamPositionCalculator::StemDirection::UNDEFINED;
   return result;
}


} // namespace MusicNotation
} // namespace AllegroFlare


