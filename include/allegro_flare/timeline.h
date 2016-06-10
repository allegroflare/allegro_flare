#ifndef __AF_TIMELINE_HEADER
#define __AF_TIMELINE_HEADER




#include <vector>
#include <allegro_flare/interpolators.h>




class Timeline
{
public:
	class Keyframe
	{
	public:
		float time;
		float val;
		float (*interpolator_func)(float);

		Keyframe(float time, float val, float (*interpolator_func)(float)=interpolator::linear);
	};

	class Track
	{
	public:
		std::string label;
		std::vector<Keyframe *> keyframe;
		float start_val;

		Track(float start_val, std::string label="");
		void add(Keyframe *k);
		void add(float time, float val, float (*interpolator_func)(float)=interpolator::linear); // shorthand
		float get_displacement(float t1, float t2);
		float get(float time);
		std::string get_str();
	};
};




#endif
