#include <fstream> // might be redundant

#include <lib/nlohmann/json.hpp>

#include <iostream>


#include <Wicked/Entity.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <Wicked/ShadowCastingLight.hpp>
#include <WickedDemos/EntityFactory.hpp>

using Wicked::Entity;

namespace AllegroFlare
{
   void to_json(nlohmann::json& j, const vec3d& v);
   void from_json(const nlohmann::json& j, vec3d& v);
   void to_json(nlohmann::json& j, const AllegroFlare::Placement3D& place);
   void from_json(const nlohmann::json& j, AllegroFlare::Placement3D& place);
}


//namespace allegro_flare
//{
   //void to_json(nlohmann::json& j, const AllegroFlare::Placement3D& place);
   //void from_json(const nlohmann::json& j, AllegroFlare::Placement3D& place);
//}



void to_json(nlohmann::json& j, const ALLEGRO_COLOR& color);
void from_json(const nlohmann::json& j, ALLEGRO_COLOR& color);

//class Camera3
//{
//public:
	//vec3d position;
	//vec3d stepout;
	//float spin;
	//float tilt;
   //float zoom;

namespace AllegroFlare::TileMaps
{
   void to_json(nlohmann::json& j, const AllegroFlare::TileMaps::PrimMeshAtlas& atlas);
   void to_json(nlohmann::json& j, const AllegroFlare::TileMaps::PrimMesh& mesh);
   void from_json(const nlohmann::json& j, AllegroFlare::TileMaps::PrimMeshAtlas& atlas);
}



namespace Wicked
{
   void to_json(nlohmann::json& j, const AllegroFlare::Camera3D& camera);
   void from_json(const nlohmann::json& j, AllegroFlare::Camera3D& camera);
   void to_json(nlohmann::json& j, const Wicked::Entity& entity);
   void from_json(const nlohmann::json& j, Wicked::Entity& entity);
}// namespace Wicked


class LevelLoader
{
private:
   std::string json_filename;

public:
   LevelLoader(std::string json_filename="/Users/markoates/Repos/Wicked/outfile.json");

   void write(
      std::vector<Wicked::Entity *> *entities,
      float time_of_day,
      Wicked::Entity *skybox,
      AllegroFlare::Camera3D &camera,
      ShadowCastingLight &casting_light
   );

   void load(
      EntityFactory &entity_factory,
      std::vector<Wicked::Entity *> &entities,
      Wicked::Entity **skybox_ptr,
      AllegroFlare::Camera3D &camera,
      AllegroFlare::Camera3D &casting_light
   );

   static void load_mesh_and_atlas(
      AllegroFlare::BitmapBin *bitmap_bin=nullptr,
      AllegroFlare::TileMaps::PrimMeshAtlas *atlas=nullptr,
      AllegroFlare::TileMaps::PrimMesh *mesh=nullptr,
      std::string json_string=""
   );
};


//// read a JSON file
//std::ifstream i("file.json");
//json j;
//i >> j;

//// write prettified JSON to another file
//std::ofstream o("pretty.json");
//o << std::setw(4) << j << std::endl;


