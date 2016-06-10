



#include <allegro_flare/bins/sample_bin.h>

#include <allegro5/allegro_acodec.h>




SampleBin::SampleBin(std::string directory)
	: Bin<ALLEGRO_SAMPLE *>(directory)
{}




SampleBin::~SampleBin()
{
	clear();
}




ALLEGRO_SAMPLE *SampleBin::load_data(std::string identifier)
{
	return al_load_sample(identifier.c_str());
}




void SampleBin::destroy_data(ALLEGRO_SAMPLE *sample)
{
	al_destroy_sample(sample);
}




