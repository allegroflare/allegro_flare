

#include <WickedDemos/ModelRepository.hpp>


ModelRepository::ModelRepository()
   : model_bin()
   , skybox(nullptr)
   , rounded_unit_cube(nullptr)
   , rounded_medium_cube(nullptr)
   , coin_ring(nullptr)
   , archway(nullptr)
   , stone_fence(nullptr)
   , flat_stage(nullptr)
   , stairbox(nullptr)
   , pointer(nullptr)
   , plate_2x2(nullptr)
   , plate_2x10(nullptr)
   , plate_10x10(nullptr)
   , mushed_up_cube(nullptr)
   //, pillar_1x1x3(nullptr)
   , initialized(false)
{}


void ModelRepository::initialize()
{
   if (initialized) return;

   
   // TODO: update this model_bin so that it is injected and the path can be dynamically coded
   std::string BASE_PATH = "/Users/markoates/Repos/allegro_flare/bin/programs/";

   model_bin.set_full_path(BASE_PATH + "data/models");

   model_bin.preload("rounded-unit-cube", "rounded_unit_cube-01.obj");
   model_bin.preload("rounded-medium-cube", "rounded_unit_cube-01.obj");
   model_bin.preload("skybox-01.obj");
   model_bin.preload("coin_ring-01.obj");
   model_bin.preload("archway-01.obj");
   model_bin.preload("unit_stone_fence-02.obj");
   model_bin.preload("pointer-01.obj");
   model_bin.preload("flat_stage-01.obj");
   model_bin.preload("plate_10x10-01.obj");
   model_bin.preload("plate_2x2-01.obj");
   model_bin.preload("plate_2x10-01.obj");
   model_bin.preload("stairbox-02.obj");
   model_bin.preload("mushed-up-cube-01.obj");
   model_bin.preload("pillar-1x1x3-01.obj");
};


Model3D *ModelRepository::get_named(std::string model_identifier)
{
   return model_bin[model_identifier];
}


Model3D *ModelRepository::get_pillar_1x1x3()
{
   return model_bin["pillar-1x1x3-01.obj"];
}


Model3D *ModelRepository::get_skybox()
{
   if (skybox) return skybox;

   skybox = model_bin["skybox-01.obj"];
   skybox->scale(10.0);
   return skybox;
}


Model3D *ModelRepository::get_mushed_up_cube()
{
   if (mushed_up_cube) return mushed_up_cube;

   mushed_up_cube = model_bin["mushed-up-cube-01.obj"];
   return mushed_up_cube;
}


Model3D *ModelRepository::get_rounded_unit_cube()
{
   if (rounded_unit_cube) return rounded_unit_cube;

   //model_bin.load("rounded-unit-cube", "rounded_unit_cube-01.obj");
   rounded_unit_cube = model_bin["rounded-unit-cube"];
   return rounded_unit_cube;
}


Model3D *ModelRepository::get_rounded_medium_cube()
{
   if (rounded_medium_cube) return rounded_medium_cube;

   //model_bin.load("rounded-medium-cube", "rounded_unit_cube-01.obj");
   rounded_medium_cube = model_bin["rounded-medium-cube"];
   rounded_medium_cube->scale(0.3);
   return rounded_medium_cube;
}


Model3D *ModelRepository::get_coin_ring()
{
   if (coin_ring) return coin_ring;

   coin_ring = model_bin["coin_ring-01.obj"];
   return coin_ring;
}


Model3D *ModelRepository::get_archway()
{
   if (archway) return archway;

   archway = model_bin["archway-01.obj"];
   archway->scale(0.5);
   return archway;
}


Model3D *ModelRepository::get_stone_fence()
{
   if (stone_fence) return stone_fence;

   stone_fence = model_bin["unit_stone_fence-02.obj"];
   stone_fence->scale(2.0);
   return stone_fence;
}


Model3D *ModelRepository::get_flat_stage()
{
   if (flat_stage) return flat_stage;

   flat_stage = model_bin["flat_stage-01.obj"];
   return flat_stage;
}


Model3D *ModelRepository::get_stairbox()
{
   if (stairbox) return stairbox;

   stairbox = model_bin["stairbox-02.obj"];
   return stairbox;
}


Model3D *ModelRepository::get_pointer()
{
   if (pointer) return pointer;

   pointer = model_bin["pointer-01.obj"];
   return pointer;
}


Model3D *ModelRepository::get_plate_2x2()
{
   if (plate_2x2) return plate_2x2;

   plate_2x2 = model_bin["plate_2x2-01.obj"];
   return plate_2x2;
}


Model3D *ModelRepository::get_plate_2x10()
{
   if (plate_2x10) return plate_2x10;

   plate_2x10 = model_bin["plate_2x10-01.obj"];
   return plate_2x10;
}


Model3D *ModelRepository::get_plate_10x10()
{
   if (plate_10x10) return plate_10x10;

   plate_10x10 = model_bin["plate_10x10-01.obj"];
   return plate_10x10;
}



