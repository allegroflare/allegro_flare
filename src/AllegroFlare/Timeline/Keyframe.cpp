

#include <AllegroFlare/Timeline/Keyframe.hpp>



namespace AllegroFlare
{
namespace Timeline
{



Timeline::Keyframe::Keyframe(float time, float val, float (*interpolator_func)(float))
   : interpolator_func(interpolator_func)
   , val(val)
   , time(time)
{}



Keyframe::~Keyframe()
{
}



} // namespace Timeline
} // namespace AllegroFlare


