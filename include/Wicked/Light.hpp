#pragma once


#include <AllegroFlare/Vec3D.hpp>

using AllegroFlare::vec3d;


class Light
{
public:
   vec3d position;
   Light(float x=0, float y=0, float z=0);
};


