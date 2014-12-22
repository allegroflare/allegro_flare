#ifndef __AF_SKELETON_HEADER
#define __AF_SKELETON_HEADER




#include <vector>

#include <allegro_flare/vec2d.h>




class Bone
{
private:
	static int _index_count; // just a helper int used for recursively counting internally

	void __count_tree_size_recursive();
	Bone *__get_nth_child_recursive(int n);

public:
	Bone *parent;
	std::vector<Bone> children;

	vec2d midpoint_direction; // TODO: this should be changed to the "0" position, not the midpoint
	float length;

	float position; // a unit value from 0 to 1 where 1 is fully rotated
	float range;

	Bone(vec2d dir_vec, float length, float tau_range=0.25);
	float get_min_angle();
	float get_max_angle();
	float get_angle();
	vec2d get_direction();
	void set_position(float unit_val);
	int get_tree_size();
	Bone *get_nth_child(int n);
	void draw(float x, float y, int index_to_hilight=-1);
	Bone *add_child(vec2d _direction, float _length, float _tau_range=0.25);
	static void __draw_recursive(Bone *bone, vec2d last_direction, vec2d pos, int index_to_hilight=-1);

	// transformations
	void scale(float amount);

	void rotate_position(float unit_val_of_joint_angle);
};







class SkeletonState
{
public:

	class BonePositionRecord
	{
	public:
		int index;
		float position;
		BonePositionRecord(int index, float position);
	};

	std::vector<BonePositionRecord> bone_positions;
	int _index_count;
	void __append_children_to_frame_recursive(Bone *bone);

public:
	SkeletonState();
	void set(Bone *bone_root);
	void save(std::string filename);
	void load(std::string filename);
	BonePositionRecord *get_frame_by_bone_index(int index);
};











#endif