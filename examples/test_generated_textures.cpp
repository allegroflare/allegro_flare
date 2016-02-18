



//
// test_generated_textures.cpp
//
// This example demonstrates some textures that are generated proceedurally.  These
// are "design primitives" that you might used to create more ellaborate graphical
// assets.
//



#include <allegro_flare/allegro_flare.h>
#include <allegro_flare/generate_textures.h>



class MyProject : public Screen
{
private:
	ALLEGRO_BITMAP *circle_render;
	ALLEGRO_BITMAP *gradient_render;
	ALLEGRO_BITMAP *circle_gradient;
	ALLEGRO_BITMAP *wood_texture;
	ALLEGRO_BITMAP *noise_texture;
	ALLEGRO_BITMAP *brush_metal_texture;

public:
	MyProject(Display *display)
		: Screen(display)
		, circle_render(NULL)
		, gradient_render(NULL)
		, circle_gradient(NULL)
		, wood_texture(NULL)
		, noise_texture(NULL)
		, brush_metal_texture(NULL)
	{
		al_set_window_title(display->al_display, "Generated Textures Test");

		circle_render = generate_circle_bitmap(128);
		gradient_render = generate_gradient_bitmap(128);
		circle_gradient = generate_circle_gradient_bitmap(128);
		noise_texture = generate_noise_bitmap(128, 128);
		wood_texture = generate_wood_grain_bitmap(128, 128);
		brush_metal_texture = generate_brush_metal_bitmap(128, 128);
	}
	void primary_timer_func() override
	{
		al_draw_bitmap(circle_render, 200, 100, ALLEGRO_FLAGS_EMPTY);
		al_draw_bitmap(gradient_render, 400, 100, ALLEGRO_FLAGS_EMPTY);
		al_draw_bitmap(circle_gradient, 600, 100, ALLEGRO_FLAGS_EMPTY);

		al_draw_bitmap(noise_texture, 200, 300, ALLEGRO_FLAGS_EMPTY);
		al_draw_bitmap(wood_texture, 400, 300, ALLEGRO_FLAGS_EMPTY);
		al_draw_bitmap(brush_metal_texture, 600, 300, ALLEGRO_FLAGS_EMPTY);
	}
};



int main(int argc, char **argv)
{
	af::initialize();
	Display *display = af::create_display(960, 540);
	MyProject *proj = new MyProject(display);
	af::run_loop();

	return 0;
}


