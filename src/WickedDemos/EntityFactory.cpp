
#include <WickedDemos/EntityFactory.hpp>


#include <WickedDemos/ModelRepository.hpp>
#include <WickedDemos/CubeMapRepository.hpp>
#include <AllegroFlare/Useful.hpp>
#include <AllegroFlare/UsefulPHP.hpp>

#include <Wicked/Entity.hpp>
//#include <Wicked/Random.hpp>

using Wicked::Entity;
//using AllegroFlare::random_float;
//using AllegroFlare::random_sign;
using AllegroFlare::TAU;


EntityFactory::EntityFactory()
   : model_repository()
   , cube_map_repository()
   , bitmap_bin()
   //, cube_map_A(nullptr)
   //, cube_map_B(nullptr)
   , cubemap_shader(nullptr)
   , simple_map_shader(nullptr)
   , standard_compound_shader(nullptr)
   , initialized(false)
   , atlas()
   , random()
{
}

AllegroFlare::TileMaps::PrimMeshAtlas &EntityFactory::get_atlas()
{
   if (initialized) throw std::runtime_error("EntityFactory::get_atlas() error: requires initialized");
   return atlas;
}

void EntityFactory::initialize()
{
   if (initialized) return;
   model_repository.initialize();
   cube_map_repository.initialize();


   // TODO: update this bitmap_bin so that it is injected and the path can be dynamically coded
   std::string BASE_PATH = "/Users/markoates/Repos/allegro_flare/bin/programs/";
   bitmap_bin.set_full_path(BASE_PATH + "data/bitmaps");

   bitmap_bin.preload("pointer-violet.png");
   bitmap_bin.preload("uv.png");
   bitmap_bin.preload("bricksz.jpg");
   bitmap_bin.preload("TexturesCom_RockSmoothErosion0015_1_seamless_S-small.png");
   bitmap_bin.preload("TexturesCom_RockSmoothErosion0015_1_seamless_S.png");

   const std::string TILE_MAP_BITMAP = "tiles_dungeon_v1.1.png";
   ALLEGRO_STATE previous_bitmap_state;
   al_store_state(&previous_bitmap_state, ALLEGRO_STATE_NEW_BITMAP_PARAMETERS);
   al_set_new_bitmap_flags(0);
   bitmap_bin.preload(TILE_MAP_BITMAP);
   atlas.duplicate_bitmap_and_load(bitmap_bin[TILE_MAP_BITMAP], 16, 16);
   al_restore_state(&previous_bitmap_state);









   std::string ROOT_PATH_TO_DATA_FOLDER = "/Users/markoates/Repos/allegro_flare/bin/";


   // load up the shaders
   std::string vertex_filename;
   std::string vertex_file_content;
   std::string fragment_filename;
   std::string fragment_file_content;

   vertex_filename = ROOT_PATH_TO_DATA_FOLDER + "data/shaders/cube_vertex.glsl";
   vertex_file_content = AllegroFlare::php::file_get_contents(vertex_filename);
   fragment_filename = ROOT_PATH_TO_DATA_FOLDER + "data/shaders/cube_fragment.glsl";
   fragment_file_content = AllegroFlare::php::file_get_contents(fragment_filename);
   cubemap_shader = new AllegroFlare::Shader(vertex_file_content, fragment_file_content);


   vertex_filename = ROOT_PATH_TO_DATA_FOLDER + "data/shaders/simple_map_vertex_with_light.glsl";
   vertex_file_content = AllegroFlare::php::file_get_contents(vertex_filename);
   fragment_filename = ROOT_PATH_TO_DATA_FOLDER + "data/shaders/simple_map_fragment_with_light.glsl";
   fragment_file_content = AllegroFlare::php::file_get_contents(fragment_filename);
   simple_map_shader = new AllegroFlare::Shader(vertex_file_content, fragment_file_content);


   vertex_filename = ROOT_PATH_TO_DATA_FOLDER + "data/shaders/standard_compound_vertex.glsl";
   vertex_file_content = AllegroFlare::php::file_get_contents(vertex_filename);
   fragment_filename = ROOT_PATH_TO_DATA_FOLDER + "data/shaders/standard_compound_fragment.glsl";
   fragment_file_content = AllegroFlare::php::file_get_contents(fragment_filename);
   standard_compound_shader = new AllegroFlare::Shader(vertex_file_content, fragment_file_content);

   //, cubemap_shader("data/shaders/cube_vertex.glsl", "data/shaders/cube_fragment.glsl")
   //, simple_map_shader("data/shaders/simple_map_vertex_with_light.glsl", "data/shaders/simple_map_fragment_with_light.glsl")
   //, standard_compound_shader("data/shaders/standard_compound_vertex.glsl", "data/shaders/standard_compound_fragment.glsl")










   cubemap_shader->initialize();
   simple_map_shader->initialize();
   standard_compound_shader->initialize();



   //const std::string TILE_MAP_BITMAP = "tiles_dungeon_v1.1.png";
   //atlas.duplicate_bitmap_and_load(bitmap_bin[TILE_MAP_BITMAP], 16, 16);

   //cube_map_A = glsl_create_cubemap_from_vertical_strip("data/bitmaps/sky4.png");
   //cube_map_B = glsl_create_cubemap_from_vertical_strip("data/bitmaps/sky5_with_grid.png");
}

Entity *EntityFactory::create_basic_mesh(int num_columns, int num_rows, vec3d position)
{
   AllegroFlare::TileMaps::PrimMesh *mesh = new AllegroFlare::TileMaps::PrimMesh(&atlas, num_columns, num_rows);
   //mesh->flip_z();
   mesh->initialize();

   //static AllegroFlare::Random random(65432);
   for (int y=0; y<mesh->get_num_rows(); y++)
   {
      for (int x=0; x<mesh->get_num_columns(); x++)
      {
         int random_tile = random.get_random_int(0, atlas.get_tile_index_size());
         //int random_tile = 4 + (5 * mesh.get_num_columns());
         mesh->set_tile_id(x, y, random_tile);
      }
   }

   Entity *entity = new Entity();
   entity->shader = standard_compound_shader; // nullptr; // simple_map_shader;
   entity->model = nullptr; //model_repository.get_flat_stage();
   entity->mesh = mesh;
   entity->diffuse_texture = atlas.get_bitmap(); //bitmap_bin["uv.png"]; // though this probably doens't matter
   entity->place.position = position;
   entity->place.rotation = vec3d(0.0, 0.0, 0.0);//tex_grass_002.jpg"];  // x=0.25 is a floor
   entity->type = "basic_mesh";
   return entity;
}

Entity *EntityFactory::create_skybox(ALLEGRO_COLOR cube_box_color, float cube_box_opacity)
{
   Entity *entity = new Entity();
   entity->model = model_repository.get_skybox();
   entity->shader = cubemap_shader;
   entity->cube_map_A = cube_map_repository.get_cube_map_B();
   entity->cube_map_B = cube_map_repository.get_cube_map_B();
   entity->cube_box_color = cube_box_color; //al_color_html("fe93f3"); //ALLEGRO_COLOR{1.0, 0.74, 0.0, 1.0};
   entity->cube_box_opacity = cube_box_opacity;
   entity->cube_map_reflecting = false;
   entity->type = "skybox";
   return entity;
}

Entity *EntityFactory::create_10x10_floor(vec3d position)
{
   Entity *entity = new Entity();
      entity->shader = simple_map_shader;
      entity->model = model_repository.get_flat_stage();
         entity->diffuse_texture = bitmap_bin["uv.png"];//tex_grass_002.jpg"];
         entity->place.position = position; // vec3d(i*10, 0, 0);//tex_grass_002.jpg"];
         //entity->place.rotation = vec3d(0.01, 0, 0.02);//tex_grass_002.jpg"];
   entity->type = "10x10_floor";
   return entity;
}

Entity *EntityFactory::create_wood_plank_01(vec3d position)
{
   return create_as_basic("wood-plank-01.obj", "Village_Tileset.png", "wood_plank_01", position);
}

Entity *EntityFactory::create_ladder_01(vec3d position)
{
   return create_as_basic("ladder-01.obj", "Village_Tileset.png", "ladder_01", position);
}

Entity *EntityFactory::create_bridge_01(vec3d position)
{
   return create_as_basic("bridge-01.obj", "Village_Tileset.png", "bridge_01", position);
}

Entity *EntityFactory::create_platform_01(vec3d position)
{
   return create_as_basic("platform-01.obj", "nature-paltformer-tileset-16x16.png", "platform_01", position);
}

Entity *EntityFactory::create_pillar_1x1x3(vec3d position)
{
   return create_as_basic("pillar-1x1x3-01.obj", "uv.png", "pillar_1x1x3", position);
}

Entity *EntityFactory::create_as_basic(std::string model_identifier, std::string texture, std::string type, vec3d position)
{
   Entity *entity = new Entity();
   entity->model = model_repository.get_named(model_identifier);
   entity->cube_map_A = cube_map_repository.get_cube_map_B();
   entity->cube_map_B = cube_map_repository.get_cube_map_B();
   entity->place.position = position;
   entity->shader = simple_map_shader;
   entity->diffuse_texture = bitmap_bin[texture];
   entity->type = type;
   return entity;
}

Entity *EntityFactory::create_mushed_up_cube(vec3d position)
{
   Entity *entity = new Entity();
   entity->model = model_repository.get_mushed_up_cube();
   entity->cube_map_A = cube_map_repository.get_cube_map_B();
   entity->cube_map_B = cube_map_repository.get_cube_map_B();
   entity->place.position = position; // vec3d(random_float(-5, 5), random_float(0, 5), random_float(-5, 5));
   //entity->place.rotation = vec3d(random_float(0, 1), random_float(0, 1), random_float(0, 1));
   //entity->velocity.rotation = vec3d(random_float(0, 0.001), random_float(0, 0.001), random_float(0, 0.001));
   entity->shader = simple_map_shader;
   //entity->shader = cubemap_shader;
   //entity->diffuse_texture = bitmaps["rounded_unit_cube_uv-01.png"];//tex_grass_002.jpg"];
   //entity->diffuse_texture = bitmaps["tex_grass_002.jpg"];
   //entity->diffuse_texture = bitmap_bin["TexturesCom_RockSmoothErosion0015_1_seamless_S.png"]; //mushed-up-cube-01.png"];
   entity->diffuse_texture = bitmap_bin["warning-block-01.png"]; //mushed-up-cube-01.png"];
   entity->type = "mushed_up_cube";
   return entity;
}

Entity *EntityFactory::create_cube(vec3d position)
{
   //static AllegroFlare::Random random(651232);

   Entity *entity = new Entity();
   entity->model = model_repository.get_rounded_unit_cube();
   entity->cube_map_A = cube_map_repository.get_cube_map_B();
   entity->cube_map_B = cube_map_repository.get_cube_map_B();
   entity->place.position = position; // vec3d(random_float(-5, 5), random_float(0, 5), random_float(-5, 5));
   entity->place.rotation = vec3d(random_float(0, 1), random_float(0, 1), random_float(0, 1));
   entity->velocity.rotation = vec3d(random_float(0, 0.001), random_float(0, 0.001), random_float(0, 0.001));
   entity->shader = simple_map_shader;
   //entity->diffuse_texture = bitmaps["rounded_unit_cube_uv-01.png"];//tex_grass_002.jpg"];
   //entity->diffuse_texture = bitmaps["tex_grass_002.jpg"];
   entity->diffuse_texture = bitmap_bin["uv.png"];
   entity->type = "cube";
   return entity;
}

Entity *EntityFactory::create_coin_ring(vec3d position)
{
   Entity *entity = new Entity();
   entity->diffuse_texture = nullptr; // bitmaps["uv.png"];
   entity->shader = cubemap_shader;
   entity->model = model_repository.get_coin_ring();
   entity->cube_map_A = cube_map_repository.get_cube_map_A();
   entity->cube_map_B = cube_map_repository.get_cube_map_A();
   entity->place.position = position; //vec3d(random_float(-5, 5), 0.5, random_float(-5, 5));
   entity->place.rotation = vec3d(0, random_float(0, 1), 0);
   entity->velocity.rotation = vec3d(0, 0.003, 0);
   entity->cube_box_color = ALLEGRO_COLOR{1.0, 0.74, 0.0, 1.0};
   entity->cube_box_opacity = 0.6;
   entity->type = "coin_ring";
   return entity;
}

Entity *EntityFactory::create_stone_fence(vec3d position)
{
   // borders to the archway
   Entity *entity = new Entity();
   entity->shader = simple_map_shader;
   entity->model = model_repository.get_stone_fence();
   entity->diffuse_texture = bitmap_bin["bricksz.jpg"];//tex_grass_002.jpg"];
   entity->place.position = position; //vec3d(-5 + i*spacing, 0, -4);
   entity->place.rotation = vec3d(0, 0.25, 0);
   entity->type = "stone_fence";
   return entity;
}

Entity *EntityFactory::create_archway(vec3d position)
{
   Entity *entity = new Entity();
   entity->shader = simple_map_shader;
   entity->model = model_repository.get_archway();
   entity->diffuse_texture = bitmap_bin["bricksz.jpg"];//tex_grass_002.jpg"];
   entity->place.position = position; //vec3d(-5 + i*spacing, 0, 0);//tex_grass_002.jpg"];
   entity->type = "archway";
   return entity;
}

Entity *EntityFactory::create_black_stone(vec3d position)
{
   Entity *entity = new Entity();
   entity->model = model_repository.get_rounded_unit_cube();
   entity->cube_map_A = cube_map_repository.get_cube_map_B();
   entity->cube_map_B = cube_map_repository.get_cube_map_B();
   entity->place.position = position; // vec3d(1.5 * i, 0.5, 3);
   entity->place.rotation = vec3d(0, random_float(0, TAU), 0);
   //entity->place.rotation = vec3d(random_float(0, 1), random_float(0, 1), random_float(0, 1));
   //entity->velocity.rotation = vec3d(random_float(0, 0.001), random_float(0, 0.001), random_float(0, 0.001));
   entity->shader = simple_map_shader;
   //entity->diffuse_texture = bitmaps["rounded_unit_cube_uv-01.png"];//tex_grass_002.jpg"];
   //entity->diffuse_texture = bitmaps["tex_grass_002.jpg"];
   entity->diffuse_texture = bitmap_bin["TexturesCom_RockSmoothErosion0015_1_seamless_S-small.png"];
   entity->type = "black_stone";
   return entity;
}

Entity *EntityFactory::create_metal_cube(vec3d position)
{
   Entity *entity = new Entity();
   entity->diffuse_texture = nullptr; // bitmaps["uv.png"];
   entity->shader = cubemap_shader;
   entity->model = model_repository.get_rounded_medium_cube();
   entity->cube_map_A = cube_map_repository.get_cube_map_A();
   entity->cube_map_B = cube_map_repository.get_cube_map_A();
   entity->place.position = position; //vec3d(random_float(-5, 5), 0.5, random_float(-5, 5));
   entity->place.rotation = vec3d(0, random_float(0, 1), 0);
   entity->velocity.rotation = vec3d(random_sign()*0.003, random_sign()*0.003, 0);
   entity->type = "metal_cube";
   return entity;
}

Entity *EntityFactory::create_stairbox(vec3d position, float y_rotation)
{
   Entity *entity = new Entity();
   entity->model = model_repository.get_stairbox();
   entity->cube_map_A = cube_map_repository.get_cube_map_B();
   entity->cube_map_B = cube_map_repository.get_cube_map_B();
   entity->place.position = position; // vec3d(1.5 * i, 0.5, 3);
   entity->place.rotation = vec3d(0, y_rotation, 0) ;//y_rotation * TAU, 0);
   //entity->place.rotation = vec3d(random_float(0, 1), random_float(0, 1), random_float(0, 1));
   //entity->velocity.rotation = vec3d(random_float(0, 0.001), random_float(0, 0.001), random_float(0, 0.001));
   entity->shader = simple_map_shader;
   //entity->diffuse_texture = bitmaps["rounded_unit_cube_uv-01.png"];//tex_grass_002.jpg"];
   //entity->diffuse_texture = bitmaps["tex_grass_002.jpg"];
   entity->diffuse_texture = bitmap_bin["TexturesCom_RockSmoothErosion0015_1_seamless_S-small.png"];
   entity->type = "stairbox";
   return entity;
}

Entity *EntityFactory::create_pointer(vec3d position)
{
   Entity *entity = new Entity();
   entity->model = model_repository.get_pointer();
   entity->cube_map_A = cube_map_repository.get_cube_map_B();
   entity->cube_map_B = cube_map_repository.get_cube_map_B();
   entity->place.position = position; // vec3d(1.5 * i, 0.5, 3);
   //entity->place.rotation = vec3d(0, y_rotation, 0) ;//y_rotation * TAU, 0);
   //entity->place.rotation = vec3d(0, 0, 0);
   entity->velocity.rotation = vec3d(0, -0.002, 0);
   entity->shader = simple_map_shader;
   //entity->diffuse_texture = bitmaps["rounded_unit_cube_uv-01.png"];//tex_grass_002.jpg"];
   //entity->diffuse_texture = bitmaps["tex_grass_002.jpg"];
   entity->diffuse_texture = bitmap_bin["pointer-violet.png"];
   entity->type = "pointer";
   return entity;
}

Entity *EntityFactory::create_plate_2x2(vec3d position, float y_rotation)
{
   Entity *entity = new Entity();
   entity->model = model_repository.get_plate_2x2();
   entity->cube_map_A = cube_map_repository.get_cube_map_B();
   entity->cube_map_B = cube_map_repository.get_cube_map_B();
   entity->place.position = position; // vec3d(1.5 * i, 0.5, 3);
   //entity->place.rotation = vec3d(0, y_rotation, 0) ;//y_rotation * TAU, 0);
   //entity->place.rotation = vec3d(0, 0, 0);
   //entity->velocity.rotation = vec3d(0, -0.002, 0);
   entity->place.rotation = vec3d(0, y_rotation, 0) ;//y_rotation * TAU, 0);
   entity->shader = simple_map_shader;
   //entity->diffuse_texture = bitmaps["rounded_unit_cube_uv-01.png"];//tex_grass_002.jpg"];
   //entity->diffuse_texture = bitmaps["tex_grass_002.jpg"];
   entity->diffuse_texture = bitmap_bin["TexturesCom_RockSmoothErosion0015_1_seamless_S.png"];
   entity->type = "plate_2x2";
   return entity;
}

Entity *EntityFactory::create_plate_2x10(vec3d position, float y_rotation)
{
   Entity *entity = new Entity();
   entity->model = model_repository.get_plate_2x10();
   entity->cube_map_A = cube_map_repository.get_cube_map_B();
   entity->cube_map_B = cube_map_repository.get_cube_map_B();
   entity->place.position = position; // vec3d(1.5 * i, 0.5, 3);
   //entity->place.rotation = vec3d(0, y_rotation, 0) ;//y_rotation * TAU, 0);
   //entity->place.rotation = vec3d(0, 0, 0);
   //entity->velocity.rotation = vec3d(0, -0.002, 0);
   entity->place.rotation = vec3d(0, y_rotation, 0) ;//y_rotation * TAU, 0);
   entity->shader = simple_map_shader;
   //entity->diffuse_texture = bitmaps["rounded_unit_cube_uv-01.png"];//tex_grass_002.jpg"];
   //entity->diffuse_texture = bitmaps["tex_grass_002.jpg"];
   entity->diffuse_texture = bitmap_bin["TexturesCom_RockSmoothErosion0015_1_seamless_S.png"];
   entity->type = "plate_2x10";
   return entity;
}

Entity *EntityFactory::create_plate_10x10(vec3d position, float y_rotation)
{
   Entity *entity = new Entity();
   entity->model = model_repository.get_plate_10x10();
   entity->cube_map_A = cube_map_repository.get_cube_map_B();
   entity->cube_map_B = cube_map_repository.get_cube_map_B();
   entity->place.position = position; // vec3d(1.5 * i, 0.5, 3);
   //entity->place.rotation = vec3d(0, y_rotation, 0) ;//y_rotation * TAU, 0);
   //entity->place.rotation = vec3d(0, 0, 0);
   //entity->velocity.rotation = vec3d(0, -0.002, 0);
   entity->place.rotation = vec3d(0, y_rotation, 0) ;//y_rotation * TAU, 0);
   entity->shader = simple_map_shader;
   //entity->diffuse_texture = bitmaps["rounded_unit_cube_uv-01.png"];//tex_grass_002.jpg"];
   //entity->diffuse_texture = bitmaps["tex_grass_002.jpg"];
   entity->diffuse_texture = bitmap_bin["TexturesCom_RockSmoothErosion0015_1_seamless_S.png"];
   entity->type = "plate_10x10";
   return entity;
}

Entity *EntityFactory::create_by_type(std::string type)
{
   if (type == "10x10_floor") return create_10x10_floor();
   if (type == "cube") return create_cube();
   if (type == "coin_ring") return create_coin_ring();
   if (type == "stone_fence") return create_stone_fence();
   if (type == "archway") return create_archway();
   if (type == "black_stone") return create_black_stone();
   if (type == "metal_cube") return create_metal_cube();
   if (type == "stairbox") return create_stairbox();
   if (type == "plate_2x2") return create_plate_2x2();
   if (type == "plate_2x10") return create_plate_2x10();
   if (type == "plate_10x10") return create_plate_10x10();
   if (type == "mushed_up_cube") return create_mushed_up_cube();
   if (type == "pillar_1x1x3") return create_pillar_1x1x3();
   if (type == "platform_01") return create_platform_01();
   if (type == "bridge_01") return create_bridge_01();
   if (type == "ladder_01") return create_ladder_01();
   if (type == "wood_plank_01") return create_wood_plank_01();
   if (type == "basic_mesh") return create_basic_mesh();
   return nullptr;
}


float EntityFactory::random_float(float min, float max)
{
   return random.get_random_float(min, max);
}


int EntityFactory::random_sign()
{
   return random.get_random_sign();
}


