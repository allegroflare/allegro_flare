#ifndef __ALLEGRO_FLARE_HEADER
#define __ALLEGRO_FLARE_HEADER



#define ALLEGRO_FLARE_VER "0.8.3"


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_memfile.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>


#include <string>
#include <vector>


#include <allegro_flare/bin.h>
#include <allegro_flare/bins/bitmap_bin.h>
#include <allegro_flare/bins/font_bin.h>
#include <allegro_flare/bins/sample_bin.h>

#include <allegro_flare/useful.h>
#include <allegro_flare/bit_flags.h>
#include <allegro_flare/profile_timer.h>

#include <allegro_flare/camera2d.h>
#include <allegro_flare/display.h>
#include <allegro_flare/screen.h>

#include <allegro_flare/interpolators.h>
#include <allegro_flare/color.h>
#include <allegro_flare/motion.h>
#include <allegro_flare/identification.h>

#include <allegro_flare/render_sample.h>
#include <allegro_flare/path2d.h>

#include <allegro_flare/objects/sound_object.h>
#include <allegro_flare/objects/text_object.h>
#include <allegro_flare/objects/bitmap_object.h>

#include <allegro_flare/file_path.h>
#include <allegro_flare/file_path_object.h>
#include <allegro_flare/config.h>

#include <zlib.h>



class af
{
public:

	static ALLEGRO_TEXTLOG *textlog;
	static ALLEGRO_JOYSTICK *joystick; // this needs some updating to allow for multiple joysticks
	static ALLEGRO_EVENT_QUEUE *event_queue;
	static ALLEGRO_FONT *builtin_font;
	static ALLEGRO_TIMER *primary_timer;
	static bool shutdown_program; // set this to true at any time to shutdown the program
	static Screen *current_screen;
	static ALLEGRO_EVENT *current_event;
	static double time_now; // used to be current_event_time
	static bool initialized;
	static ConfigSettings *config; // thinking of removing this and replacing it with the DataAttr config file thing

	static int key_alt, key_shift, key_ctrl;
	static bool drawing_profiler_graph;

	static void initialize(std::string config_filename="");
	static Display *create_display(int width=960, int height=540);
	static Display *create_display(int width, int height, int display_flags);
	static Display *create_display(int width, int height, int display_flags, int adapter);
	static Display *create_display(int width, int height, bool fullscreen);
	static Display *create_display(int width, int height, bool fullscreen, int adapter);
	static Display *create_display(Display::resolution_t resolution);

	static void use_screen(Screen *screen);
	static void run_loop();

	static void open_log_window();
	static void close_log_window();
	static void log(std::string message);
};





#endif