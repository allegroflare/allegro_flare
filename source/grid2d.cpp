



#include <allegro_flare/grid2d.h>

#include <algorithm>
#include <allegro_flare/useful.h> // to replace the issues surrounding std::sprintf




grid2d::grid2d()
	: horizontal_guide()
	, vertical_guide()
{}




void grid2d::add_horizontal_guide(float x)
{
	horizontal_guide.push_back(x);
}




void grid2d::add_vertical_guide(float y)
{
	vertical_guide.push_back(y);
}




float grid2d::get_max_horizontal_guide()
{
	std::vector<float>::iterator it = std::max_element(horizontal_guide.begin(), horizontal_guide.end());
	return (it==horizontal_guide.end()) ? 0 : *it;
}




float grid2d::get_max_vertical_guide()
{
	std::vector<float>::iterator it = std::max_element(vertical_guide.begin(), vertical_guide.end());
	return (it==vertical_guide.end()) ? 0 : *it;
}




float grid2d::get_min_horizontal_guide()
{
	std::vector<float>::iterator it = std::min_element(horizontal_guide.begin(), horizontal_guide.end());
	return (it==horizontal_guide.end()) ? 0 : *it;
}




float grid2d::get_min_vertical_guide()
{
	std::vector<float>::iterator it = std::min_element(vertical_guide.begin(), vertical_guide.end());
	return (it==vertical_guide.end()) ? 0 : *it;
}




int grid2d::get_closest_horizontal_guide_index(float x, float threshold)
{
	int index = 0;
	float dist = std::abs(x - horizontal_guide[index]);

	for (int i=0; i<(int)horizontal_guide.size(); i++)
	{
		float this_distance = std::abs(x - horizontal_guide[i]);
		if (this_distance < dist)
		{
			dist = this_distance;
			index = i;
		}
	}
	return index;
}




int grid2d::get_closest_vertical_guide_index(float y, float threshold)
{
	int index = 0;
	float dist = std::abs(y - vertical_guide[index]);

	for (int i=0; i<(int)vertical_guide.size(); i++)
	{
		float this_distance = std::abs(y - vertical_guide[i]);
		if (this_distance < dist)
		{
			dist = this_distance;
			index = i;
		}
	}
	return index;
}




int grid2d::get_closest_coordinate_index_to_the_left(float x)
{
	float closest = 0;
	int closest_index = 0;
	bool found = false;

	for (unsigned i=0; i<horizontal_guide.size(); i++)
	{
		if (horizontal_guide[i] >= x) continue;

		float distance = std::abs(x - horizontal_guide[i]);
		if ((!found) || (distance < closest))
		{
			closest = distance;
			closest_index = i;
			found = true;
		}
	}

	if (!found) return -1;
	return closest_index;
}




int grid2d::get_closest_coordinate_index_above(float y)
{
	float closest = 0;
	int closest_index = 0;
	bool found = false;

	for (unsigned i=0; i<vertical_guide.size(); i++)
	{
		if (vertical_guide[i] >= y) continue;

		float distance = std::abs(y - vertical_guide[i]);
		if ((!found) || (distance < closest))
		{
			found = true;
			closest = distance;
			closest_index = i;
		}
	}

	if (!found) return -1;
	return closest_index;
}




vec2d grid2d::get_closest_coordinates(float x, float y, float threshold)
{
	int hgi = get_closest_horizontal_guide_index(x);
	int vgi = get_closest_vertical_guide_index(y);
	return vec2d(get_horizontal_guide_pos(hgi), get_vertical_guide_pos(vgi));
}




vec2d grid2d::get_closest_left_coordinate(float x, float y)
{
	int index = 0;
	bool found = false;
	float shortest_distance = 0;


	for (int i=0; i<(int)horizontal_guide.size(); i++)
	{
		if (horizontal_guide[i] >= x) continue;

		float this_distance = std::abs(x - horizontal_guide[i]);

		if (!found)
		{
			found = true;
			shortest_distance = this_distance;
			index = i;
		}
		else
		{
			if (this_distance < shortest_distance)
			{
				index = i;
				shortest_distance = this_distance;
			}
		}
	}

	if (!found) return vec2d(0, 0);

	int vgi = get_closest_vertical_guide_index(y);
	return vec2d(get_horizontal_guide_pos(index), get_vertical_guide_pos(vgi));
}




void grid2d::draw_guides(ALLEGRO_COLOR color)
{
	float left = get_min_horizontal_guide();
	float top = get_min_vertical_guide();
	float width = get_max_horizontal_guide();
	float height = get_max_vertical_guide();

	// draw horizontals
	for (unsigned i=0; i<horizontal_guide.size(); i++)
	{
		al_draw_line(horizontal_guide[i], top, horizontal_guide[i], height, color, 1.0);
	}

	// draw verticals
	for (unsigned i=0; i<vertical_guide.size(); i++)
	{
		al_draw_line(left, vertical_guide[i], width, vertical_guide[i], color, 1.0);
	}

	//al_draw_rectangle(0, 0, width, height, color::black, 2.0);
}




void grid2d::draw_guide_numbers(ALLEGRO_FONT *font, float padding, ALLEGRO_COLOR color)
{
	float left = get_min_horizontal_guide();
	float top = get_min_vertical_guide();
	//float width = get_max_horizontal_guide();
	//float height = get_max_vertical_guide();

	//char str[32];
	std::string str_;

	// draw horizontals
	for (unsigned i=0; i<horizontal_guide.size(); i++)
	{
		//std::sprintf(str, "%d", i);
		str_ = tostring(i);
		//al_draw_line(horizontal_guide[i], top, horizontal_guide[i], height, color::black, 1.0);
		al_draw_text(font, color, horizontal_guide[i], top - padding - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER, str_.c_str());
	}

	// draw verticals
	for (unsigned i=0; i<vertical_guide.size(); i++)
	{
		//std::sprintf(str, "%d", i);
		str_ = tostring(i);
		//al_draw_line(left, vertical_guide[i], width, vertical_guide[i], color::black, 1.0);
		al_draw_text(font, color, left - padding, vertical_guide[i] - al_get_font_ascent(font)/2, ALLEGRO_ALIGN_RIGHT, str_.c_str());
	}

	//al_draw_rectangle(0, 0, width, height, color::black, 2.0);
}




float grid2d::get_horizontal_guide_pos(int index)
{
	if (index < 0) return 0;
	if (index >= (int)horizontal_guide.size()) return 0;
	return horizontal_guide[index];
}




float grid2d::get_vertical_guide_pos(int index)
{
	if (index < 0) return 0;
	if (index >= (int)vertical_guide.size()) return 0;
	return vertical_guide[index];
}




vec2d grid2d::get_guide_pos(int x_index, int y_index)
{
	return vec2d(get_horizontal_guide_pos(x_index), get_vertical_guide_pos(y_index));
}




