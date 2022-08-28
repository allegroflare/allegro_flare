

#include <AllegroFlare/MultiMeshUV.hpp>



namespace AllegroFlare
{


MultiMeshUV::MultiMeshUV(float u1, float v1, float u2, float v2)
   : u1(u1)
   , v1(v1)
   , u2(u2)
   , v2(v2)
{
}


MultiMeshUV::~MultiMeshUV()
{
}


void MultiMeshUV::set_u1(float u1)
{
   this->u1 = u1;
}


void MultiMeshUV::set_v1(float v1)
{
   this->v1 = v1;
}


void MultiMeshUV::set_u2(float u2)
{
   this->u2 = u2;
}


void MultiMeshUV::set_v2(float v2)
{
   this->v2 = v2;
}


float MultiMeshUV::get_u1() const
{
   return u1;
}


float MultiMeshUV::get_v1() const
{
   return v1;
}


float MultiMeshUV::get_u2() const
{
   return u2;
}


float MultiMeshUV::get_v2() const
{
   return v2;
}


float MultiMeshUV::infer_width()
{
   return u2-u1;
}

float MultiMeshUV::infer_height()
{
   return v2-v1;
}
} // namespace AllegroFlare


