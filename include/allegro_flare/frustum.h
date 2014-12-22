#ifndef __AF_FRUSTUM_HEADER
#define __AF_FRUSTUM_HEADER




struct Frustum
{
public:
	float znear, zfar;
	float top, left, right, bottom;
	Frustum(int width=800, int height=600, int znear=500, float multiplier=0.01);
};





#endif