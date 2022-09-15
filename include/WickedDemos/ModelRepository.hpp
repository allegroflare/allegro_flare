#pragma once


#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Model3D.hpp>


using AllegroFlare::ModelBin;
using AllegroFlare::Model3D;


class ModelRepository
{
private:
   ModelBin model_bin;
   Model3D *skybox;
   Model3D *rounded_unit_cube;
   Model3D *rounded_medium_cube;
   Model3D *coin_ring;
   Model3D *archway;
   Model3D *stone_fence;
   Model3D *flat_stage;
   Model3D *stairbox;
   Model3D *pointer;
   Model3D *plate_2x2;
   Model3D *plate_2x10;
   Model3D *plate_10x10;
   Model3D *mushed_up_cube;
   //Model3D *pillar_1x1x3;
   bool initialized;

public:
   ModelRepository();

   void initialize();

   Model3D *get_named(std::string model_identifier="asdf");
   Model3D *get_pillar_1x1x3();
   Model3D *get_skybox();
   Model3D *get_mushed_up_cube();
   Model3D *get_rounded_unit_cube();
   Model3D *get_rounded_medium_cube();
   Model3D *get_coin_ring();
   Model3D *get_archway();
   Model3D *get_stone_fence();
   Model3D *get_flat_stage();
   Model3D *get_stairbox();
   Model3D *get_pointer();
   Model3D *get_plate_2x2();
   Model3D *get_plate_2x10();
   Model3D *get_plate_10x10();
};



