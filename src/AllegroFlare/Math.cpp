

#include <AllegroFlare/Math.hpp>



namespace AllegroFlare
{


Math::Math()
{
}


Math::~Math()
{
}


const float Math::PI = 3.14159265358979323846;


const float Math::TAU = PI * 2;


const float Math::FULL_ROTATION = TAU;


float Math::degrees_to_radians(float deg)
{
   return PI * deg / 180.0f;
}


float Math::radians_to_degrees(float radians)
{
    return 180.0f / PI * radians;
}




} // namespace AllegroFlare


