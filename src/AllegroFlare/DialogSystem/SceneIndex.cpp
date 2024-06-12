

#include <AllegroFlare/DialogSystem/SceneIndex.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogSystem
{


SceneIndex::SceneIndex()
   : scenes({})
{
}


SceneIndex::~SceneIndex()
{
}


void SceneIndex::set_scenes(std::map<std::string, AllegroFlare::DialogSystem::Scenes::Base*> scenes)
{
   this->scenes = scenes;
}


std::map<std::string, AllegroFlare::DialogSystem::Scenes::Base*> &SceneIndex::get_scenes_ref()
{
   return scenes;
}


int SceneIndex::num_scenes()
{
   return scenes.size();
}

std::vector<std::string> SceneIndex::get_scene_names()
{
   std::vector<std::string> result;
   for (auto &scene : scenes)
   {
      result.push_back(scene.first);
   }
   return result;
}

void SceneIndex::add_scene(std::string name, AllegroFlare::DialogSystem::Scenes::Base* scene)
{
   if (!(scene))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DialogSystem::SceneIndex::add_scene]: error: guard \"scene\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DialogSystem::SceneIndex::add_scene]: error: guard \"scene\" not met");
   }
   if (!((!scene_exists_by_name(name))))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DialogSystem::SceneIndex::add_scene]: error: guard \"(!scene_exists_by_name(name))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DialogSystem::SceneIndex::add_scene]: error: guard \"(!scene_exists_by_name(name))\" not met");
   }
   scenes[name] = scene;
}

bool SceneIndex::scene_exists_by_name(std::string name)
{
   return (scenes.find(name) != scenes.end());
}

AllegroFlare::DialogSystem::Scenes::Base* SceneIndex::find_scene_by_name(std::string name)
{
   if (!(scene_exists_by_name(name)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DialogSystem::SceneIndex::find_scene_by_name]: error: guard \"scene_exists_by_name(name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DialogSystem::SceneIndex::find_scene_by_name]: error: guard \"scene_exists_by_name(name)\" not met");
   }
   // TODO: This guard results in a double lookup. Might be faster to integrate it below.
   if (scenes.find(name) == scenes.end()) return nullptr;
   return scenes[name];
}


} // namespace DialogSystem
} // namespace AllegroFlare


