

#include <allegro_flare/bins/model_bin.h>








ModelBin::ModelBin(std::string directory)
	: Bin<Model *>(directory)
{}




ModelBin::~ModelBin()
{
	clear();
}




Model *ModelBin::load_data(std::string identifier)
{
	Model *m = new Model();
	if (m->load_obj_file(identifier, color::white)) return m;
	delete m;
	return NULL;
}




void ModelBin::destroy_data(Model *mdl)
{
	//al_destroy_bitmap(mdl);
	if (!mdl) return;
	mdl->clear();
	delete mdl;
}

