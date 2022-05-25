

#include <AllegroFlare/Timeline/Keyframe.hpp>



namespace AllegroFlare
{
namespace Timeline
{



Timeline::Keyframe::Keyframe(float time, float val, float (*interpolator_func)(float))
   : time(time)
   , val(val)
   , interpolator_func(interpolator_func)
{}



Keyframe::~Keyframe()
{
}



} // namespace Timeline
} // namespace AllegroFlare


