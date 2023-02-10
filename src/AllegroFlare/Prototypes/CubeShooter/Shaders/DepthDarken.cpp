

#include <AllegroFlare/Prototypes/CubeShooter/Shaders/DepthDarken.hpp>

#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace CubeShooter
{
namespace Shaders
{


DepthDarken::DepthDarken()
   : AllegroFlare::Shaders::Base("CubeShooter/Shaders/DepthDarken", obtain_vertex_source(), obtain_fragment_source())
   , torch_type(0)
   , initialized(false)
{
}


DepthDarken::~DepthDarken()
{
}


void DepthDarken::initialize()
{
   if (!initialized) AllegroFlare::Shaders::Base::initialize();
   initialized = true;
}

void DepthDarken::set_torch_type(int type)
{
   torch_type = type;
}

void DepthDarken::set_torch_on()
{
   torch_type = 1;
}

void DepthDarken::set_torch_off()
{
   torch_type = 0;
}

void DepthDarken::activate()
{
   if (!initialized) throw std::runtime_error("[CubeShooter::Shaders::DepthDarken] Attempting to activate() shader before it has been initialized");
   AllegroFlare::Shaders::Base::activate();
   AllegroFlare::Shaders::Base::set_int("torch_type", torch_type);
}

void DepthDarken::deactivate()
{
   AllegroFlare::Shaders::Base::deactivate();
}

std::string DepthDarken::obtain_vertex_source()
{
   static const std::string source = R"DELIM(
     attribute vec4 al_pos;
     attribute vec4 al_color;
     attribute vec2 al_texcoord;
     uniform mat4 al_projview_matrix;
     varying vec4 varying_color;
     varying vec2 varying_texcoord;

     void main()
     {
        varying_color = al_color;
        varying_texcoord = al_texcoord;
        gl_Position = al_projview_matrix * al_pos;
     }
   )DELIM";
   return source;
}

std::string DepthDarken::obtain_fragment_source()
{
   static const std::string source = R"DELIM(
     uniform sampler2D al_tex;
     uniform float tint_intensity;
     uniform vec3 tint;
     uniform int torch_type;
     varying vec4 varying_color;
     varying vec2 varying_texcoord;

     void main()
     {
        vec4 tmp = texture2D(al_tex, varying_texcoord);
        //float noise = 1.0; //noise1(3)* 0.1 + 0.9;

        //bool torch_type = false;
        if (torch_type == 1) // regular torch
        {
           vec4 torch_color = (vec4(0.96, 0.804, 0.2941, 1.0) + vec4(1., 1., 1., 1.)) * 0.7;
           float depth_value = gl_FragCoord.a;
           //float inverse_tint_intensity = 1.0 - tint_intensity;
           tmp.r = tmp.r * depth_value * torch_color.r;// * noise;
           tmp.g = tmp.g * depth_value * torch_color.g;// * noise;
           tmp.b = tmp.b * depth_value * torch_color.b;// * noise;
           //tmp.a = tmp.a;
        }
        else if (torch_type == 2) // torch_of_truth
        {
           vec4 torch_color = (vec4(0.73, 0.744, 0.79, 1.0) + vec4(1., 1., 1., 1.)) * 0.8;
           float depth_value = (gl_FragCoord.a * 0.96) + 0.04;

           //float inverse_tint_intensity = 1.0 - tint_intensity;
           tmp.r = tmp.r * depth_value * torch_color.r;// * noise;
           tmp.g = tmp.g * depth_value * torch_color.g;// * noise;
           tmp.b = tmp.b * depth_value * torch_color.b;// * noise;
           //tmp.a = tmp.a;
        }
        else
        {
           //float depth_value = (gl_FragCoord.a < 0.2) ? 0.0 : gl_FragCoord.a;
           float depth_value = smoothstep(0.05, 0.25, (gl_FragCoord.a * 0.5)) * 0.25; // ? 0.0 : gl_FragCoord.a;
           //float inverse_tint_intensity = 1.0 - tint_intensity;
           tmp.r = tmp.r * depth_value;
           tmp.g = tmp.g * (depth_value + 0.004);
           tmp.b = tmp.b * (depth_value + 0.02);
           //tmp.a = tmp.a;
        }

        gl_FragColor = tmp;
     }
   )DELIM";
   return source;
}


} // namespace Shaders
} // namespace CubeShooter
} // namespace Prototypes
} // namespace AllegroFlare


