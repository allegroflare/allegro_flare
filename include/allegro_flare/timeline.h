#ifndef __AF_TIMELINE_HEADER
#define __AF_TIMELINE_HEADER





#include <vector>
#include <algorithm>
#include <sstream>
#include <allegro_flare/interpolators.h>




namespace Timeline
{

	
	
template <class T>
class Keyframe
{
public:
	float time;
	T val;
	float (*interpolator_func)(float);
	Keyframe(float time, T val, float (*interpolator_func)(float)=interpolator::linear)
		: time(time)
		, val(val)
		, interpolator_func(interpolator_func)
	{}
};



template <class T>
bool keyframe_sort_func(const Keyframe<T> *k1, const Keyframe<T> *k2)
{
	return k1->time < k2->time;
}


/**
	Track consists of a list of keyframes that can play in sequence.
*/
template <class T>
class Track
{
public:
	std::string label;
	std::vector<Keyframe<T> *> keyframe;
	T start_val;

	Track(T start_val, std::string label="")
		: label(label)
		, start_val(start_val)
	{}

	void add(Keyframe<T> *k)
	{
		keyframe.push_back(k);
		std::sort(keyframe.begin(), keyframe.end(), keyframe_sort_func<T>);
	}

	/**
		Adds a keyframe into the track.

		@param time the time in seconds relative to the beginning of the track, which is 0.
		@param val the value that is set at that time.
		@param interpolator_func the function pointer to a function that interpolates the values from the
			previous value to the one in this keyframe.
	*/
	void add(float time, T val, float (*interpolator_func)(float)=interpolator::linear) // shorthand
	{
		keyframe.push_back(new Keyframe<T>(time, val, interpolator_func));
		std::sort(keyframe.begin(), keyframe.end(), keyframe_sort_func<T>);
	}

	/**
		Get the difference between the values at two time positions.  Note, this is not the distance traveled,
		or the velocity, which may be what you're looking for.

		@param time the time in seconds relative to the beginning of the track, which is 0.
		@param val the value that is set at that time.
		@param interpolator_func the function pointer to a function that interpolates the values from the
			previous value to the one in this keyframe.
	*/
	T get_displacement(float t1, float t2)
	{
		return get(t2) - get(t1);
	}

	/**
		Get the value at the given time.

		@param time the time in seconds.
	*/
	T get(float time)
	{
		Keyframe<T> *right=NULL;
		float left_time = 0;
		T *left_val = &start_val;

		if (keyframe.empty() || time < 0) return start_val;
		else if (time >= keyframe.back()->time) return keyframe.back()->val;
		else if (time <= keyframe.front()->time)
		{
			right = keyframe.front();
		}
		else
		{
			// would probably be faster in a binary search?
			for (unsigned i=1; i<keyframe.size(); i++)
				if (keyframe[i-1]->time < time && time < keyframe[i]->time)
				{
					left_val = &keyframe[i-1]->val;
					left_time = keyframe[i-1]->time;
					right = keyframe[i];
					break;
				}
		}

		float time_width = right->time - left_time;
		float time_in = time - left_time;
		float time_normal = time_in / time_width;

		T val_delta = right->val - *left_val;

		return right->interpolator_func(time_normal) * val_delta + *left_val;
	}

	/**
		Returns a string with a list of frames, their times, values, and interpolatorsd
	*/
	std::string get_str()
	{
		std::ostringstream ss;
		ss << "timeline: " << label << std::endl;
		for (unsigned i=0; i<keyframe.size(); i++)
			ss << "  frame " << i << ": (" << keyframe[i]->time << ", " << keyframe[i]->val << ", " << __func__(keyframe[i]->interpolator_func) << ")" << std::endl;

		return ss.str();
	}
};



}




#endif