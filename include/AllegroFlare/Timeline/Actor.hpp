#pragma once


#include <vector>
#include <string>
#include <AllegroFlare/Timeline/Track.hpp>


typedef int actor_t;


namespace AllegroFlare
{
   namespace Timeline
   {
      class Actor
      {
      public:
         actor_t type;
         std::string identifier;
         std::vector<AllegroFlare::Timeline::Track *> params;


         Actor(std::string identifier, actor_t type);
         virtual ~Actor();

         AllegroFlare::Timeline::Track *get_param_by_id(const char *id);

         virtual void load_script(std::string script);
         virtual void load_script(std::vector<std::string> script_lines);
         virtual void render(double time) = 0;
         virtual void register_params() = 0;
      };
   }
}



