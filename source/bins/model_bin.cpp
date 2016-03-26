

#include <allegro_flare/bins/model_bin.h>








ModelBin::ModelBin(std::string directory)
	: Bin<ModelNew *>(directory)
{}




ModelBin::~ModelBin()
{
	clear();
}




ModelNew *ModelBin::load_data(std::string identifier)
{
	ModelNew *m = new ModelNew();
	if (m->load_obj_file(identifier.c_str(), 1.0f)) return m;
	delete m;
	return NULL;
}




void ModelBin::destroy_data(ModelNew *mdl)
{
	if (!mdl) return;
	delete mdl;
}

