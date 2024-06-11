#include <Wicked/LevelLoader.hpp>

#include <fstream> // might be redundant
#include <AllegroFlare/JSONLoaders/AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/JSONLoaders/AllegroFlare/Vec3D.hpp>
#include <AllegroFlare/JSONLoaders/Allegro.hpp>

#include <lib/nlohmann/json.hpp>

//void to_json(nlohmann::json& j, const placement3d& entity)
//{
//}


#include <iostream>


#include <Wicked/Entity.hpp>

using Wicked::Entity;
using AllegroFlare::Placement3D;


namespace AllegroFlare
{
   //void to_json(nlohmann::json& j, const vec3d& v)
   //{
      //j = nlohmann::json{
         //{"x", v.x},
         //{"y", v.y},
         //{"z", v.z},
      //};
   //}

   //void from_json(const nlohmann::json& j, vec3d& v)
   //{
      //j.at("x").get_to(v.x);
      //j.at("y").get_to(v.y);
      //j.at("z").get_to(v.z);
   //}

   void to_json(nlohmann::json& j, const AllegroFlare::Placement3D& place)
   {
      j = nlohmann::json{
         {"position", place.position},
         {"size", place.size},
         {"align", place.align},
         {"scale", place.scale},
         {"anchor", place.anchor},
         {"rotation", place.rotation},
      };
   }

   void from_json(const nlohmann::json& j, AllegroFlare::Placement3D& place)
   {
      j.at("position").get_to(place.position);
      j.at("size").get_to(place.size);
      j.at("align").get_to(place.align);
      j.at("scale").get_to(place.scale);
      j.at("anchor").get_to(place.anchor);
      j.at("rotation").get_to(place.rotation);
   }
}



//void to_json(nlohmann::json& j, const ALLEGRO_COLOR& color)
//{
   //j = nlohmann::json{
      //{"r", color.r},
      //{"g", color.g},
      //{"b", color.b},
      //{"a", color.a},
   //};
//}

//void from_json(const nlohmann::json& j, ALLEGRO_COLOR& color)
//{
   //j.at("r").get_to(color.r);
   //j.at("g").get_to(color.g);
   //j.at("b").get_to(color.b);
   //j.at("a").get_to(color.a);
//}


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
   void to_json(nlohmann::json& j, const AllegroFlare::TileMaps::PrimMeshAtlas& atlas)
   {
      j = nlohmann::json{
         { "bitmap_filename", atlas.get_bitmap_filename() },
         { "tile_width", atlas.get_tile_width() },
         { "tile_height", atlas.get_tile_height() },
         { "tile_spacing", atlas.get_tile_spacing() },
         //{ "num_rows", mesh.get_num_rows() },
         //{ "num_columns", mesh.get_num_columns() },
      };
   }

   void from_json(const nlohmann::json& j, AllegroFlare::TileMaps::PrimMeshAtlas& atlas)
   {
      // get the values
      std::string bitmap_filename = "";
      int tile_width = 1;
      int tile_height = 1;
      int tile_spacing = 0;

      // clear the atlas
      //atlas.clear();

      j.at("bitmap_filename").get_to(bitmap_filename);
      j.at("tile_width").get_to(tile_width);
      j.at("tile_height").get_to(tile_height);
      j.at("tile_spacing").get_to(tile_spacing);

      atlas.set_bitmap_filename(bitmap_filename);
      atlas.set_tile_width(tile_width);
      atlas.set_tile_height(tile_height);
      atlas.set_tile_spacing(tile_spacing);

      // clear the atlas
      //atlas.clear();
   }

   void to_json(nlohmann::json& j, const AllegroFlare::TileMaps::PrimMesh& mesh)
   {
      j = nlohmann::json{
         {"num_rows", mesh.get_num_rows()},
         {"num_columns", mesh.get_num_columns()},
         //{"atlas", mesh.get_atlas()},
         {"tiles", mesh.get_tile_ids()},
      };

      AllegroFlare::TileMaps::PrimMeshAtlas *atlas_ptr = mesh.get_atlas();
      if (atlas_ptr)
      {
         AllegroFlare::TileMaps::PrimMeshAtlas &atlas = (*atlas_ptr);
         j["atlas"] = atlas;
      }
      //if mesh
   }

   //void from_json(nlohmann::json& j, AllegroFlare::TileMaps::PrimMesh& mesh)
   //{
      ////placement3d place = j["place"].get<placement3d>();

      //j.at("num_rows").get_to(entity.type);
      //j.at("place").get_to(entity.place);
      //j.at("velocity").get_to(entity.velocity);
   //}
}



//namespace AllegroFlare
//{


//void to_json(nlohmann::json& j, const AllegroFlare::Camera3D& camera)
//{
   //j = nlohmann::json{
      //{"position", camera.position},
      //{"stepout", camera.stepout},
      //{"spin", camera.spin},
      //{"tilt", camera.tilt},
      //{"zoom", camera.zoom},
   //};
//}


//void from_json(const nlohmann::json& j, AllegroFlare::Camera3D& camera)
//{
   //j.at("position").get_to(camera.position);
   //j.at("stepout").get_to(camera.stepout);
   //j.at("spin").get_to(camera.spin);
   //j.at("tilt").get_to(camera.tilt);
   //j.at("zoom").get_to(camera.zoom);
//}


//} // namespace AllegroFlare




namespace Wicked
{

void to_json(nlohmann::json& j, const Wicked::Entity& entity)
{
   j = nlohmann::json{
      {"type", entity.type},
      {"place", entity.place},
      {"velocity", entity.velocity},
   };

   if (entity.mesh)
   {
      j["mesh"] = (*(entity.mesh));
   }
}


void from_json(const nlohmann::json& j, Wicked::Entity& entity)
{
   //AllegroFlare::Placement3D place = j["place"].get<AllegroFlare::Placement3D>();

   j.at("type").get_to(entity.type);
   j.at("place").get_to(entity.place);
   //entity.place = place;
   j.at("velocity").get_to(entity.velocity);

   AllegroFlare::Placement3D place = entity.place; //j["place"].get<AllegroFlare::Placement3D>();

   //std::cout << "AAAAAAA" << entity.place.position.x << std::endl;
}



}// namespace Wicked































LevelLoader::LevelLoader(std::string json_filename)
   : json_filename(json_filename)
{}



void LevelLoader::write(
      std::vector<Wicked::Entity *> *entities,
      float time_of_day,
      Wicked::Entity *skybox,
      AllegroFlare::Camera3D &camera,
      ShadowCastingLight &casting_light
   )
{
   if (!entities) throw std::runtime_error("NO entities there!");
   if (!skybox) throw std::runtime_error("need skybox in LevelLoader::write");

   std::ofstream o;
   o.open(json_filename, std::ofstream::out);

   nlohmann::json result;

   // write time_of_day
   result["time_of_day"] = time_of_day;
   result["camera"] = camera;
   result["casting_light"] = casting_light;

   if (skybox)
   {
      result["skybox_color"] = skybox->cube_box_color;
      result["skybox_color_opacity"] = skybox->cube_box_opacity;
   }

   // write entities
   result["entities"] = {};
   for (auto &entity_ptr : *entities)
   {
      Wicked::Entity &entity = (*entity_ptr);
      nlohmann::json j = entity;
      result["entities"] += j;
   }

   o << std::setw(3) << result << std::endl;

   o.close();
}



void LevelLoader::load(
      EntityFactory &entity_factory,
      std::vector<Wicked::Entity *> &entities,
      Wicked::Entity **skybox_ptr,
      AllegroFlare::Camera3D &camera,
      AllegroFlare::Camera3D &casting_light
   )
{
   if (!skybox_ptr) throw std::runtime_error("need skybox_ptr in LevelLoader::load");
   //if (!camera) throw std::runtime_error("need camera in LevelLoader::load");
   //if (!casting_light) throw std::runtime_error("need casting_light in LevelLoader::load");

   AllegroFlare::TileMaps::PrimMeshAtlas &atlas = entity_factory.get_atlas();

   std::ifstream infile(json_filename);
   nlohmann::json j;
   infile >> j;


   //skybox_ptr = entity_factory.create_skybox(); 
   // todo clear the skybox
   Wicked::Entity *skybox = entity_factory.create_skybox();//al_color_html("fe93f3"), 0.6);
   if (j.contains("skybox_color")) { j.at("skybox_color").get_to(skybox->cube_box_color); }
   if (j.contains("skybox_color_opacity")) { j.at("skybox_color_opacity").get_to(skybox->cube_box_opacity); }
   (*skybox_ptr) = skybox;
   
   if (j.contains("camera")) { j.at("camera").get_to(camera); }
   if (j.contains("casting_light")) { j.at("casting_light").get_to(casting_light); }

   nlohmann::json json_entities = j["entities"];
   for (auto &json_entity : json_entities)
   {
      //nlohmann::json json = *entities[0];
      Wicked::Entity e = json_entity.get<Wicked::Entity>();

      //std::cout << "type: " << e.type << std::endl;
      //std::cout << "place: " << e.place.position.x << std::endl;

      Wicked::Entity *created_entity = entity_factory.create_by_type(e.type);
      created_entity->place = e.place;

      if (json_entity.contains("mesh"))
      {
         nlohmann::json mesh_json_entity = json_entity["mesh"];
         int num_columns = 0;
         int num_rows = 0;
         std::vector<int> tiles;

         mesh_json_entity.at("num_columns").get_to(num_columns);
         mesh_json_entity.at("num_rows").get_to(num_rows);
         mesh_json_entity.at("tiles").get_to(tiles);

         if ((int)tiles.size() != (num_rows * num_columns))
         {
            std::stringstream error_message;
            error_message << "LevelLoader::load] loading mesh, num_columns*num_rows (" << num_rows*num_columns << ") "
               "needs to equal tiles.size(), which is (" << tiles.size() << ") but it does not";
            throw std::runtime_error(error_message.str().c_str());
         }

         if (created_entity->mesh)
         {
            AllegroFlare::Random random;
            created_entity->mesh->resize(num_columns, num_rows);
            for (int y=0; y<created_entity->mesh->get_num_rows(); y++)
            {
               for (int x=0; x<created_entity->mesh->get_num_columns(); x++)
               {
                  //std::vector<int> elements = {172, 173, 174, 175, 176, 177, 192, 193, 194, 195, 196, 197};
                  //int random_tile = random_element(elements); //random.get_random_int(0, atlas.get_tile_index_size());
                  int tile = tiles[x + y*created_entity->mesh->get_num_columns()];
                  //int random_tile = 4 + (5 * mesh.get_num_columns());
                  created_entity->mesh->set_tile_id(x, y, tile);
               }
            }
         }
      }

      entities.push_back(created_entity);
   }
}


void LevelLoader::load_mesh_and_atlas(
      AllegroFlare::BitmapBin *bitmap_bin,
      AllegroFlare::TileMaps::PrimMeshAtlas *atlas,
      AllegroFlare::TileMaps::PrimMesh *mesh,
      std::string json_string
   )
{
   if (!bitmap_bin) throw std::runtime_error("LevelLoader::load_mesh_and_atlas needs valid bitmap_bin");
   if (!atlas) throw std::runtime_error("LevelLoader::load_mesh_and_atlas needs valid atlas");
   if (!mesh) throw std::runtime_error("LevelLoader::load_mesh_and_atlas needs valid mesh");

   // TODO: this
   // parse the json
   // set the json values to the atlas
   // set the json values to the mesh
   // refresh the atlas
   // refresh the mesh
}


//// read a JSON file
//std::ifstream i("file.json");
//json j;
//i >> j;

//// write prettified JSON to another file
//std::ofstream o("pretty.json");
//o << std::setw(4) << j << std::endl;



