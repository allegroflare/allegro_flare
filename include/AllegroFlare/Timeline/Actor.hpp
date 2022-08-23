#pragma once


#include <vector>
#include <string>
#include <AllegroFlare/Timeline/Track.hpp>


namespace AllegroFlare
{
   namespace Timeline
   {
      class Actor
      {
      public:
         std::string type;
         std::string identifier;
         std::vector<AllegroFlare::Timeline::Track *> params;


         Actor(std::string type="Actor", std::string identifier="[unset-identifier]");
         virtual ~Actor();

         AllegroFlare::Timeline::Track *get_param_by_id(const char *id);

         virtual void load_script(std::string script);
         virtual void load_script(std::vector<std::string> script_lines);
         virtual void render(double time) = 0;
         virtual void register_params() = 0;
      };
   }
}



