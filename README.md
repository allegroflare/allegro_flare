![](http://zeoxdesign.com/images/allegro_flare_logo-04.png) AllegroFlare
=============

Current version - Development on v0.8.5


AllegroFlare is a C++ framework based on the Allegro 5 game programming library.

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

Framework
- All initialization with one function (`af::initialize()`)
- Easy system interface with one class (`Screen`)
- virtual member functions to grab events (`primary_timer_func()`, `mouse_axes_func()`, `joy_down_func()`, `key_char_func()`, etc)

Resource Management
- Use any image, sample, or font by filename (`af::bitmaps["mypic.jpg"]`, `af::fonts["Times.ttf 16"]`, etc)
- Bins for media files (`FontBin`, `SampleBin`, `BitmapBin`)

Graphics
- 2D path shapes (`path2d`)
- 2D and 3D tools (`vec2d`, `vec3d`, `placement2d`, `placement3d`, `Camera2D`, `Camera3D`, etc)
- 3D model loading (`Model`)
- Basic image manipulation (`gaussian_blur()`, `color_overlay()`, `trim()`, `invert()`, etc)
- Image generation (`draw_wav_sample()`, `draw_histogram()`, `create_gradient_bitmap()`, etc)
- Music notation (`MusicNotation`)

Motion
- timing control and animation (`Motion`)
- easing functions (`interpolator::fastIn`, `interpolator::trippleSlowInOut`, `interpolator::bounceIn`, etc)

Scripting and Animation
- Timelines for playback (`Timeline`, `Stage`, `Actor`, `Script`)
- Make any of your class's functions accessible from a script (`Scriptable`)
- Add attributes to objects for saving/loading/scripting (`Attr`, `ElementID`, `AttrLoader`)

GUI
- (see the [FlareGUI project](https://github.com/MarkOates/flare_gui))

Color
- Color creation and manipulation (`mix()`, `change_hue()`, `change_lightness()`, etc.)
- Operators for math with ALLEGRO_COLORs (`+`, `-`, `*`, `==`)
- Many color definitions (`color::yellowgreen`, `color::blue`, `color::plum`, `color::floralwhite`, etc)

Encryption
- md5 and sha2 functions

Other cool stuff (requires dependencies)
- Interprocess and Shared Memory (boost)
- Text-to-speech API (windows)
- Download a file (curl)
- webcam (OpenCV)
- theatre lighting control (dmx-box)
- MIDI (windows)

And More
- Bone trees, profiling timers, file path access, php-like functions, chainable media objects, etc..

Dependencies
============

AllegroFlare requires Allegro 5.1.10 or greater.  You can also include other features with CURL, OpenCV, and Boost.
