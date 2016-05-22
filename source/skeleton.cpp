#include <allegro_flare/skeleton.h>




#include <allegro5/allegro_primitives.h>

#include <allegro_flare/color.h>

#include <allegro_flare/useful.h>
#include <allegro_flare/useful_php.h>




void Bone::__count_tree_size_recursive()
{
	for (unsigned i=0; i<children.size(); i++)
	{
		_index_count++;
		children[i].__count_tree_size_recursive();
	}
}



Bone *Bone::__get_nth_child_recursive(int n)
{
	for (unsigned i=0; i<children.size(); i++)
	{
		_index_count++;
		if (n == _index_count) return &children[i];
		Bone *bone = children[i].__get_nth_child_recursive(n);
		if (bone) return bone;
	}
	return NULL;
}



Bone::Bone(vec2d dir_vec, float length, float tau_range)
	: parent(NULL)
	, children()
	, midpoint_direction(dir_vec.normalized())
	, length(length)
	, position(0.5)
	, range(tau_range * TAU)
{}



float Bone::get_min_angle()
{
	return midpoint_direction.get_angle() - range / 2;
}



float Bone::get_max_angle()
{
	return midpoint_direction.get_angle() + range / 2;
}



float Bone::get_angle()
{
	return get_min_angle() + range * position;
}



vec2d Bone::get_direction()
{
	return vec2d::polar_coords(get_angle(), 1.0);
}



#include <algorithm>

void Bone::set_position(float unit_val)
{
	position = std::min<float>(1.0, std::max<float>(0.0, unit_val));
	//direction = (get_max_angle() - get_min_angle()) / 2
}



int Bone::get_tree_size()
{
	_index_count = 1;
	__count_tree_size_recursive();
	return _index_count;
}



Bone *Bone::get_nth_child(int n)
{
	_index_count = 0;
	if (n==0) return this;
	return __get_nth_child_recursive(n);
}



void Bone::draw(float x, float y, int index_to_hilight)
{
	_index_count = 0;
	vec2d end_pos = get_direction() * length;
	al_draw_line(x, y, x+end_pos.x, y+end_pos.y, color::white, 2.0);
	__draw_recursive(this, get_direction(), vec2d(x, y) + end_pos, index_to_hilight);
	al_draw_rectangle(x-5, y-5, x+5, y+5, color::yellowgreen, 2.0);
}



Bone *Bone::add_child(vec2d _direction, float _length, float _tau_range)
	// note: _direction is the direction of the central point of rotation
	// tau_range is a value from 0 to 1, denominating the unit value of TAU which is the range of the rotation
{
	children.push_back(Bone(_direction, _length, _tau_range));
	return &children.back();
}



void Bone::__draw_recursive(Bone *bone, vec2d last_direction, vec2d pos, int index_to_hilight)
{
	unsigned i = 0;
	Bone *child = NULL;
	vec2d direction = 0;

	for (i=0; i<bone->children.size(); i++)
	{
		_index_count++;

		child = &bone->children[i];

		float direction_ang = last_direction.get_angle() + child->get_angle();
		direction = vec2d::polar_coords(direction_ang, 1);
			
		vec2d start = pos;
		vec2d end = pos + direction * child->length;
		//direction = (end - start).normalized();

		// draw the bone and the endpoints
		if (_index_count == index_to_hilight) al_draw_line(start.x, start.y, end.x, end.y, color::pink, 8.0);
		al_draw_line(start.x, start.y, end.x, end.y, color::white, 2.0);
		al_draw_circle(start.x, start.y, 4, color::dodgerblue, 2.0);
		al_draw_circle(end.x, end.y, 6, color::orange, 2.0);

		// draw the angle bounds
		al_draw_arc(start.x, start.y, 18, direction_ang-child->range/2, child->range, color::color(color::dodgerblue, 0.4), 9);

		__draw_recursive(child, direction, end, index_to_hilight);
	}
}



void Bone::scale(float amount)
{
	length *= amount;
	for (unsigned i=0; i<children.size(); i++)
	{
		children[i].scale(amount);
	}
}



void Bone::rotate_position(float unit_val_of_joint_angle)
{
	set_position(position + unit_val_of_joint_angle);
}



int Bone::_index_count = 0;









SkeletonState::BonePositionRecord::BonePositionRecord(int index, float position)
	: index(index)
	, position(position)
{}







void SkeletonState::__append_children_to_frame_recursive(Bone *bone)
{
	bone_positions.push_back(BonePositionRecord(_index_count, bone->position));
	_index_count++;
	for (unsigned i=0; i<bone->children.size(); i++)
	{
		__append_children_to_frame_recursive(&bone->children[i]);
	}
}



SkeletonState::SkeletonState() {}



void SkeletonState::set(Bone *bone_root)
{
	bone_positions.clear();
	_index_count = 0;
	__append_children_to_frame_recursive(bone_root);
}



void SkeletonState::save(std::string filename)
{
	std::stringstream content;
	for (unsigned i=0; i<bone_positions.size(); i++)
	{
		content << bone_positions[i].index << " " << bone_positions[i].position << std::endl;
	}
	php::file_put_contents(filename, content.str());
}



void SkeletonState::load(std::string filename)
{
	if (!php::file_exists(filename))
	{
		std::cout << "file not found." << std::endl;
		return;
	}
	bone_positions.clear();
	std::vector<std::string> lines = php::explode("\n", php::file_get_contents(filename));
	for (unsigned i=0; i<lines.size(); i++)
	{
		std::vector<std::string> tokens = php::explode(" ", lines[i]);
		if (tokens.size() != 2) continue;

		int index = atoi(tokens[0].c_str());
		float position = atof(tokens[1].c_str());

		bone_positions.push_back(BonePositionRecord(index, position));
	}
}



SkeletonState::BonePositionRecord *SkeletonState::get_frame_by_bone_index(int index)
{
	for (unsigned i=0; i<bone_positions.size(); i++)
	{
		if (bone_positions[i].index == index) return &bone_positions[i];
	}
	return NULL;
}


