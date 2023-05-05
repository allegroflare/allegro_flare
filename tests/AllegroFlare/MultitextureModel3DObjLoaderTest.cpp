
#include <gtest/gtest.h>

#include <AllegroFlare/MultitextureModel3DObjLoader.hpp>


TEST(AllegroFlare_MultitextureModel3DObjLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MultitextureModel3DObjLoader multitexture_model3dobj_loader;
}


TEST(AllegroFlare_MultitextureModel3DObjLoaderTest, load__will_not_blow_up)
{
   AllegroFlare::MultitextureModel3D model;
   model.initialize();
   AllegroFlare::MultitextureModel3DObjLoader multitexture_model3dobj_loader;
   multitexture_model3dobj_loader.set_model(&model);

   multitexture_model3dobj_loader.load();
}


