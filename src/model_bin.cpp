



#include <allegro_flare/model_bin.h>




ModelBin::ModelBin(std::string directory)
   : Bin<Model3D *>(directory)
{}




ModelBin::~ModelBin()
{
   clear();
}




Model3D *ModelBin::load_data(std::string identifier)
{
   Model3D *m = new Model3D();
   if (m->load_obj_file(identifier.c_str(), 1.0f)) return m;
   delete m;
   return NULL;
}




void ModelBin::destroy_data(Model3D *mdl)
{
   if (!mdl) return;
   delete mdl;
}




