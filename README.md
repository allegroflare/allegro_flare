![](http://zeoxdesign.com/images/allegro_flare_logo-04.png) AllegroFlare
=============

Current version - Development on v0.8.5


AllegroFlare is an C++ framework based on the Allegro 5 game programming library.  All of the regular functionality of Allegro remains intact with AllegroFlare, but now with an expanded feature set and tons of cool stuff.  Using the framework makes for fast and fun development, or, you can cherry-pick any of the fantastic classes and functions provided by AllegroFlare and use them in your vanilla Allegro program.

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


Some Examples of Features and Tools
============

### Framework
- Initialize (basically) everything with one function (`af::initialize()`)
- Interface with the system through a parent class (`Screen`)
- Use virtual member functions to grab events (`primary_timer_func()`, `mouse_axes_func()`, `joy_button_down_func()`, `key_char_func()`, etc)
- Access assets through global media bins (`af::bitmaps["mypic.jpg"]`, `af::fonts["Times.ttf 16"]`, etc)

### Resource Management
- Bins for media files (`FontBin`, `SampleBin`, `BitmapBin`)
- Use any image, sample, or font by filename

### Graphics
- 2D path shapes (`path2d`)
- 2D and 3D positioning tools (`vec2d`, `vec3d`, `placement2d`, `placement3d`)
- cameras (`Camera2D`, `Camera3D`)
- 3D model loading (`Model`)
- Basic image manipulation (`gaussian_blur()`, `color_overlay()`, `trim()`, `color_curve()`, `invert()`, etc)
- Image generation (`draw_wav_sample()`, `draw_histogram()`, `create_gradient_bitmap()`, etc)
- Create music notation (`MusicNotation`)

### Motion
- timing and movement control (`Motion`)
- easing functions (`interpolator::fastIn`, `interpolator::trippleSlowInOut`, `interpolator::bounceIn`, etc)

### Scripting and Animation
- Use useful clases to automate playback of your objects (`Motion`, `Timeline`, `Stage`, `Actor`, `Script`)
- Use any member function from your classes in a script (`Scriptable`)
- Add attributes to your classes for scripting, saving, and loading (`Attr`, `ElementID`, `AttrLoader`)

### GUI
- (see the [FlareGUI project](https://github.com/MarkOates/flare_gui))

### Color
- Color creation and manipulation (`mix()`, `change_hue()`, `change_lightness()`, etc.)
- Operators for ALLEGRO_COLORs (`+`, `-`, `*`, `==`)
- Many color definitions (`color::yellowgreen`, `color::blue`, `color::plum`, `color::floralwhite`, etc)

### Encryption
- md5 and sha2 functions

### Other cool stuff (requires dependencies)
- Interprocess and Shared Memory (boost)
- Text-to-speech API (windows)
- Download a file in a thread (curl)
- Webcam access (OpenCV)
- Theatre lighting control (dmx-box)
- MIDI control (windows)

### And More
- Bone trees, profiling timers, file path access, php-like functions, chainable media objects, etc..

Dependencies
============

AllegroFlare requires Allegro 5.1.10 or greater.  You can also include other features with CURL, OpenCV, and Boost.
