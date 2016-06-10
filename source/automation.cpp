



#include <allegro_flare/automation.h>

#include <allegro_flare/useful.h>




namespace automation
{




std::string BasicScriptReader::remove_comments(std::string &line)
{
	std::size_t comment_pos = line.find("//");
	if (comment_pos == std::string::npos) return line;
	else return line.substr(0, comment_pos);
}




BasicScriptReader::BasicScriptReader(std::string script)
	: current_line_index(0)
{
	lines = php::explode("\n", script);
};




bool BasicScriptReader::at_end()
{
	if (current_line_index >= lines.size()) return true;
	return false;
}




std::string BasicScriptReader::get_next_line(bool remove_comments)
{
	return (remove_comments) ? BasicScriptReader::remove_comments(lines[current_line_index++]) : lines[current_line_index++];
}




//
// Actor
//




Actor::Actor(std::string identifier, actor_t type)
	: type(type)
	, identifier(identifier)
{
	//register_params();
}




Timeline::Track *Actor::get_param_by_id(const char *id)
{
	for (unsigned i=0; i<params.size(); i++)
		if (params[i]->label == id) return params[i];
	std::cout << "cannot find param \"" << identifier << "." << id << "\"" << std::endl;
	return NULL;
}




void Actor::load_script(std::string script_filename)
{
	for (unsigned i=0; i<params.size(); i++)
		params[i]->keyframe.clear();

	BasicScriptReader script_reader(php::file_get_contents(script_filename));
	while (!script_reader.at_end())
	{
		std::vector<std::string> tokens = php::explode(" ", script_reader.get_next_line());
		// oh, let's go with this format:
		// [time_sec] [param] [value] [!interpoltor]
			
		if (tokens.size() != 4) continue;

		double time_sec = atof(tokens[0].c_str());
		Timeline::Track *param = get_param_by_id(tokens[1].c_str());
		float val = atof(tokens[2].c_str());
		interpolator::interpolator_func_t interpolator_func = interpolator::get_interpolator_by_name(tokens[3]);
		param->add(time_sec, val, interpolator_func);
	}
}




//
// Actor2D
// 



	
Actor2D::Actor2D(std::string identifier, ALLEGRO_BITMAP *bitmap)
	: Actor(identifier, 1)
	, bitmap(bitmap)
{
	register_params();
}




void Actor2D::register_params()
{
	//std::cout << "Here";
	params.clear();
	params.push_back(new Timeline::Track(0, "x"));
	params.push_back(new Timeline::Track(0, "y"));
	params.push_back(new Timeline::Track(0.5, "align_x"));
	params.push_back(new Timeline::Track(0.5, "align_y"));
	params.push_back(new Timeline::Track(1, "scale_x"));
	params.push_back(new Timeline::Track(1, "scale_y"));
	params.push_back(new Timeline::Track(0, "rotation"));
	params.push_back(new Timeline::Track(1, "opacity"));
}




void Actor2D::render(double time)
{
	al_draw_tinted_scaled_rotated_bitmap(
		bitmap,
		color::color(color::white, get_param_by_id("opacity")->get(time)),
		al_get_bitmap_width(bitmap) * get_param_by_id("align_x")->get(time),
		al_get_bitmap_height(bitmap) * get_param_by_id("align_y")->get(time),
		get_param_by_id("x")->get(time),
		get_param_by_id("y")->get(time),
		get_param_by_id("scale_x")->get(time),
		get_param_by_id("scale_y")->get(time),
		get_param_by_id("rotation")->get(time),
		ALLEGRO_FLAGS_EMPTY);
}




//
// ActorManager
//




ActorManager::ActorManager()
{}




//Actor *ActorManager::create_actor2d(std::string identifier, ALLEGRO_BITMAP *bitmap)
//{
//	actors.push_back(new Actor2D(identifier, bitmap));
//	return actors.back();
//}




bool ActorManager::register_actor(Actor *actor)
{
	if (get_actor_by_id(actor->identifier.c_str())) return false;

	actors.push_back(actor);
	return true;
}




bool ActorManager::unregister_actor(Actor *actor)
{
	// this could be optimized
	for (unsigned i=0; i<actors.size(); i++)
		if (actors[i]->identifier == actor->identifier)
		{
			actors.erase(actors.begin()+i);
			return true;
		}
	return false;
}




Actor *ActorManager::get_actor_by_id(const char *id)
{
	for (unsigned i=0; i<actors.size(); i++)
		if (actors[i]->identifier == id) return actors[i];
	return NULL;
}




void ActorManager::render(double time)
{
	for (unsigned i=0; i<actors.size(); i++)
		actors[i]->render(time);
}




} // (end namespace automation)




