

#include <allegro_flare/allegro_flare.h>




class MyProject : public Screen
{
public:
	MyProject(Display *display) : Screen(display) {}
	void primary_timer_func() override
	{
		al_draw_bitmap(af::bitmaps["pun_dog.jpg"], 125, 150, 0);
	
		al_draw_filled_rectangle(750-10-25, 200-10, 1200+10-25, 200+300+10, color::gray);	
		draw_histogram(af::bitmaps["pun_dog.jpg"], 750-25, 200, 450, 300, color::white);
	}
};



int main(int argc, char **argv)
{
	af::initialize();
	Display *display = af::create_display();
	MyProject *proj = new MyProject(display);
	af::run_loop();
	return 0;
}


