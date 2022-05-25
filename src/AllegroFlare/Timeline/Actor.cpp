

#include <AllegroFlare/Timeline/Actor.hpp>

#include <iostream> // for cout. TODO: replace
#include <AllegroFlare/Timeline/ScriptLoader.hpp>
#include <AllegroFlare/UsefulPHP.hpp>



namespace AllegroFlare
{
namespace Timeline
{


      Actor::Actor(std::string identifier, actor_t type)
         : type(type)
           , identifier(identifier)
      {
         //register_params();
      }




      Actor::~Actor()
      {
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

         ScriptLoader script_reader(AllegroFlare::php::file_get_contents(script_filename));
         while (!script_reader.at_end())
         {
            std::vector<std::string> tokens = AllegroFlare::php::explode(" ", script_reader.get_next_line());
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



} // namespace Timeline
} // namespace AllegroFlare


