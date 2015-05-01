

#include <allegro_flare/allegro_flare.h>
#include <allegro_flare/image_processing.h>


class MaskedBitmapExampleProgram : public Screen
{
private:
	ALLEGRO_BITMAP *bitmap;
	
public:
	MaskedBitmapExampleProgram(Display *display) : Screen(display)
	{
		bitmap = create_masked_bitmap(af::bitmaps["rooster_cat_grid.png"], af::bitmaps["elm_circle.png"]);
	}
	void primary_timer_func() override
	{
		al_draw_bitmap(af::bitmaps["rooster_cat_grid.png"], 100, 100, 0);
		al_draw_bitmap(af::bitmaps["elm_circle.png"], 400, 100, 0);
		al_draw_bitmap(bitmap, 700, 100, 0);
	}
};


int main(int argc, char **argv)
{
	af::initialize();
	Display *display = af::create_display(1100, 500);
	MaskedBitmapExampleProgram *prog = new MaskedBitmapExampleProgram(display);
	af::run_loop();
}



