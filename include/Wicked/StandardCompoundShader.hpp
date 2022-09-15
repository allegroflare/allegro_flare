#pragma once

//#include <AllegroFlare/Shader.hpp>
//using AllegroFlare::Shader;


#include <allegro_flare/shader.h>
using allegro_flare::Shader;


extern Shader *standard_compound_shader;

Shader *__get_standard_compound_shader();

