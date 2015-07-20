#ifndef __AF_MODEL_BIN_HEADER
#define __AF_MODEL_BIN_HEADER





#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <allegro_flare/bin.h>
#include <allegro_flare/model.h>



class ModelBin : public Bin<ModelNew *>
{
public:
	ModelBin(std::string directory="data/models");
	~ModelBin();
	ModelNew *load_data(std::string identifier);
	void destroy_data(ModelNew *bmp);
};





#endif
