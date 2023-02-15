

#define ALLEGRO_UNSTABLE

#include <AllegroFlare/CubemapTextureBinder.hpp>

#include <AllegroFlare/Cubemap.hpp>
#include <iostream> // for cout, TODO: replace with AllegroFlare::Logger



namespace AllegroFlare
{


CubemapTextureBinder::CubemapTextureBinder(std::string name, AllegroFlare::Cubemap *cubemap, int unit)
   : name(name)
   , cubemap(cubemap)
   , unit(unit)
{
}


CubemapTextureBinder::~CubemapTextureBinder()
{
}


bool CubemapTextureBinder::bind()
{
   if (!cubemap) return false;
   // grab the currently active shader program
   GLint currProgram;
   glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
   GLint shader_program_object = currProgram;

   // get and verify that the uniform name is there and valid
   GLint handle = glGetUniformLocation(shader_program_object, name.c_str());
   if (handle < 0)
   {
      // this warning is silenced because there are instances where a user
      // intentionally attempts to assign the uniform even knowing it is not there.
      // a better reporting mechanisim might be used for all Shader::set_* functions.
      //std::cout << "uniform not found for \"" << name << "\" in shader" << std::endl;
      return false;
   }

   // bind it
   glActiveTexture(GL_TEXTURE0 + unit);
   glBindTexture(GL_TEXTURE_CUBE_MAP_EXT, cubemap->get_id());
   glUniform1i(handle, unit);

   // check for errors
   GLenum err = glGetError();
   if (err != 0)
   {
      // NOTE: in the internal Allegro 5 code, this pattern returns the acual message, rather
      // than the error number.  However, the funciton to get the message for the error
      // is an internal Allegro function.  This will work for now.
      std::cout << "[Shader::set_sampler] error: glGetError() returned " << err << std::endl;
      return err;
   }
   return true;
}


} // namespace AllegroFlare


