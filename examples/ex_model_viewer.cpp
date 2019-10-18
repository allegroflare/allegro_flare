



#include <allegro_flare/allegro_flare.h>




using namespace allegro_flare;
using namespace AllegroFlare;



class Project : public Screen
{
public:
   Camera3D camera;
   BitmapBin bitmaps;
   Model3D *model;

   Project(Display *display)
      : Screen(display)
      , camera(vec3d(0, 0, -5), vec3d(0, 0, 1), vec3d(0, 1, 0))
      , model(new Model3D())
   {
      model->load_obj_file("data/models/heart_item-01.obj");
      model->set_texture(bitmaps["heart_item-02.png"]);
   }

   void primary_timer_func() override
   {
      camera.set_frustum_as_camera(display->al_display);

      if (model)
      {
         ALLEGRO_TRANSFORM t;
         al_identity_transform(&t);
         al_rotate_transform_3d(&t, 0, 1, 0, al_get_time()*0.5);
         al_use_transform(&t);

         model->draw();
      }
   }
};




int main(int argc, char *argv[])
{
   Framework::initialize();
   Display *display = Framework::create_display(800, 600);
   Project *proj = new Project(display);
   Framework::run_loop();
   return 0;
}




