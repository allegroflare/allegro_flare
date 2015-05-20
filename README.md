![](http://zeoxdesign.com/images/allegro_flare_logo-04.png) AllegroFlare
=============

Current version - Development on v0.8.5


AllegroFlare is a C++ framework based on the Allegro 5 game programming library.  Several classes/functions are provided that are not dependent on using the framework.

Simple Example
============

```cpp
#include <allegro_flare/allegro_flare.h>

class MyApp : public Screen
{
public:
    MyApp(Display *display) : Screen(display) {}
    void primary_timer_func() override
    {
        al_draw_filled_rectangle(300, 400, 200, 100, color::chartreuse);
    }
}

int main(int argc, char **argv)
{
    af::initialize(); // initialize all things AllegroFlare
    Display *display = af::create_display(800, 600); // creates a new Window
    MyApp *my_app = new MyApp(display); // creates a new instance of your app
    af::run_loop(); // run the AllegroFlare framework
}
```


Some Features and Tools
============

- Motion based tools (Motion, Timeline, Stage, Actor, Script)
- Resource managing tools (FontBin, SampleBin, BitmapBin)
- Color tools (hex(), name(), adjust_hue(), adjust_brigtness(), etc.)
- Simple CURL wrapper
- Scripting tools (Scriptable, ProgrammingLanguage)
- Graphics tools
- 2D and 3D tools (Camera2D, Camera3D, placement2d, placement3d, Model)
- 3D model loading (Model)
- 2D path shapes (Path2D)
- Interprocess and Shared Memory
- Text-to-speech API


Dependencies
============

AllegroFlare requires Allegro 5.1 or greater.  You can also include other features with CURL, OpenCV, and Boost.

