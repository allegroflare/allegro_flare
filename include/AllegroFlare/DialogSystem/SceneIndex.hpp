#pragma once


#include <AllegroFlare/DialogSystem/Scenes/Base.hpp>
#include <map>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      class SceneIndex
      {
      private:
         std::map<std::string, AllegroFlare::DialogSystem::Scenes::Base*> scenes;

      protected:


      public:
         SceneIndex();
         ~SceneIndex();

         void set_scenes(std::map<std::string, AllegroFlare::DialogSystem::Scenes::Base*> scenes);
         std::map<std::string, AllegroFlare::DialogSystem::Scenes::Base*> &get_scenes_ref();
         int num_scenes();
         std::vector<std::string> get_scene_names();
         void add_scene(std::string name="[unset-name]", AllegroFlare::DialogSystem::Scenes::Base* scene=nullptr);
         bool scene_exists_by_name(std::string name="[unset-name]");
         AllegroFlare::DialogSystem::Scenes::Base* find_scene_by_name(std::string name="[unset-name]");
      };
   }
}



