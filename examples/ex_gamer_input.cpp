
/*

GAMER INPUT EXAMPLE PROGRAM

ex_gamer_input.cpp

This simple example handles user events that are emitted by GamerInputScreen (which captures input from
either the keyboard and/or a joystick) to move a red box around on the screen.

*/



#include <allegro_flare/allegro_flare.h>

#include <allegro_flare/screens/gamer_input_screen.h>
#include <allegro_flare/screens/simple_notification_screen.h>





class MyProject : public Screen
{
public:
	bool moving_up = false;
	bool moving_down = false;
	bool moving_left = false;
	bool moving_right = false;

	placement2d box_placement;

	GamerInputScreen *gamer_input_screen;
	SimpleNotificationScreen *simple_notification_screen;

	MyProject(Display *display)
		: Screen(display)
		, box_placement(400, 300, 30, 30)
		, gamer_input_screen(NULL)
		, simple_notification_screen(NULL)
	{
		gamer_input_screen = new GamerInputScreen(display);
		simple_notification_screen = new SimpleNotificationScreen(display, af::fonts["DroidSans.ttf 20"]);
	}
	void primary_timer_func() override
	{
		// update movement
		if (moving_up) box_placement.position.y -= 1;
		if (moving_down) box_placement.position.y += 1;
		if (moving_left) box_placement.position.x -= 1;
		if (moving_right) box_placement.position.x += 1;

		// draw everything
		al_draw_rectangle(box_placement.position.x, box_placement.position.y,
			box_placement.position.x+box_placement.size.x, box_placement.position.y+box_placement.size.y,
			color::red, 6.0);
	}
	void user_event_func() override
	{
		switch(af::current_event->type)
		{
		case ALLEGRO_EVENT_GAMER_BUTTON_UP:
			if (af::current_event->user.data1 == GAMER_BUTTON_UP) moving_up = false;
			if (af::current_event->user.data1 == GAMER_BUTTON_DOWN) moving_down = false;
			if (af::current_event->user.data1 == GAMER_BUTTON_LEFT) moving_left = false;
			if (af::current_event->user.data1 == GAMER_BUTTON_RIGHT) moving_right = false;
			break;
		case ALLEGRO_EVENT_GAMER_BUTTON_DOWN:
			if (af::current_event->user.data1 == GAMER_BUTTON_UP) moving_up = true;
			if (af::current_event->user.data1 == GAMER_BUTTON_DOWN) moving_down = true;
			if (af::current_event->user.data1 == GAMER_BUTTON_LEFT) moving_left = true;
			if (af::current_event->user.data1 == GAMER_BUTTON_RIGHT) moving_right = true;
			break;
		}
	}
	void joy_config_func() override
	{
		if (simple_notification_screen)
		{
			if (af::joystick != NULL)
			{
				std::stringstream notification_message;
				notification_message << "New joystick added\n" << al_get_joystick_name(af::joystick);
				simple_notification_screen->spawn_notification(notification_message.str());
			}
			else
			{
				simple_notification_screen->spawn_notification("Joystick disconnected");
			}
		}
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




