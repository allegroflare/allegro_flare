#include <allegro_flare/allegro_flare.h>

#include <allegro_flare/camera3d.h>
#include <allegro_flare/model.h>




class Project : public Screen
{
public:
	Camera3D camera;
	BitmapBin bitmaps;
	Model *model;

	Project(Display *display)
		: Screen(display)
		, camera(vec3d(0, 0, -5), vec3d(0, 0, 1), vec3d(0, 1, 0))
		, model(new Model())
	{
		model->load_obj_file("data/models/heart_item-01.obj");
		model->textures.set_texture(0, bitmaps["heart_item-01tx.png"]);
	}

	void primary_timer_func() override
	{
		camera.set_frustum_as_camera(display->display);
		if (model) model->draw();
	}
};




int main(int argc, char *argv[])
{
	af::initialize();
	Display *display = af::create_display(800, 600);

	Project *proj = new Project(display);

	af::run_loop();
}