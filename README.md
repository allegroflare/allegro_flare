![Allegro Flare](bin/data/bitmaps/allegro_flare_logo-04.png?raw=true) AllegroFlare
=============

* Current in-development version - v0.9.0wip on `master`
* Latest stable version - [v0.8.9 - Sassy
Seadragon](https://github.com/allegroflare/allegro_flare/releases/tag/v0.8.9)


AllegroFlare is a game programming library in C++.  It's built on top of the [Allegro 5 Game Programming Library](http://liballeg.org), extending it with new features to make your game development expreience all the more enjoyable.



Build Instructions
-----------------------------------

AllegroFlare works on Windows, Linux, and OSX.  Before compiling, you'll need to have [Allegro 5.2.0](http://liballeg.org/) or greater on your system.  If you're using `gcc` or `clang`, the process for building is the same on all systems.

#### Step 1: Clone the repo
```
$ git clone https://github.com/MarkOates/allegro_flare.git
```

#### Step 2: Set your directories in `Makefile`
At the top of the `Makefile` are 4 variables.  Edit them to point to the locations where you have Allegro and AllegroFlare on your computer.  If you're on Windows, your `LIBS_ROOT` might be something like `C:/Users/Repos/`.
```makefile
LIBS_ROOT=/Users/markoates/Repos
ALLEGRO_DIR=$(LIBS_ROOT)/allegro5
ALLEGRO_LIB_DIR=$(LIBS_ROOT)/allegro5/build/lib
ALLEGROFLARE_DIR=$(LIBS_ROOT)/allegro_flare
```

#### Step 3: Run Make
```
$ make
```
Success!  The only thing left to do is `#include <allegro_flare/allegro_flare.h>` in your program, and link with the AllegroFlare lib and the Allegro libs when compiling.  Optionally, you can build the example programs with `make examples`.

If you run into any problems or have questions, ask on the [allegro.cc forums](http://www.allegro.cc/forums/recent).

Simple Example
--------------

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
    Framework::initialize(); // initialize all things AllegroFlare
    Display *display = Framework::create_display(800, 600); // creates a new Window
    MyApp *my_app = new MyApp(display); // creates a new instance of your app
    Framework::run_loop(); // run the AllegroFlare framework
}
```



Some Examples of Features and Tools
-----------------------------------

### Framework
- Initialize (basically) everything with one function (`Framework::initialize()`)
- Interface with the system through a parent class (`Screen`)
- Use virtual member functions to grab events (`primary_timer_func()`, `mouse_axes_func()`, `joy_button_down_func()`, `key_char_func()`, etc.)
- Get any asset by filename (`Framework::bitmap("mypic.jpg")`, `Framework::font("Times.ttf 16")`, etc.)

### Resource Management
- Bins for media files (`FontBin`, `SampleBin`, `BitmapBin`)
- Use any image, sample, or font by filename

### Graphics
- Easily position, size, rotate and draw images with (`BitmapObject`)
- Draw to offscreen bitmaps / Cache expensive renders (`RenderCache`)
- Use 3D models (`Model3D`)
- Use cameras for better placement/views (`Camera2D`, `Camera3D`)
- Use shaders (`Shader`)
- Easily place objects in 2D and 3D space (`vec2d`, `vec3d`, `placement2d`, `placement3d`)
- Modify images with filters (`gaussian_blur()`, `color_overlay()`, `trim()`, `color_curve()`, `invert()`, etc.)
- Generate images from data (`draw_wav_sample()`, `draw_histogram()`, `create_gradient_bitmap()`, etc.)
- Create paths (`path2d`)
- Create music notation (`MusicNotation`)

### GUI
- Interface with the GUI through the parent class `UIScreen`
- Use from a list of usefull widgets `UIButton`, `UICheckbox`, `UIDial`, `UIFramedWindow`, `UIImage`, `UIIntSpinner`, `UILabeledCheckbox`, `UIListSpinner`, `UIMusicNotation`, `UIPickingBuffer`, `UIProgressBar`, `UIScaledText`, `UIScreen`, `UIScrollArea`, `UIScrollBar`, `UISpinner`, `UIVerticalSlider`, `UIText`, `UITextArea`, `UITextBox`, `UITextInput`, `UITextList`, `UIToggleButton`, `UIXYController`, `UIWidget`, `UIWindow`
- Easily create your own widget by inheriting from `UIWidget`

### Motion
- timing and movement control (`Motion`)
- easing functions (`interpolator::fast_in`, `interpolator::tripple_slow_in_out`, `interpolator::bounce_in`, etc.)

### Scripting and Animation
- Use useful clases to automate playback of your objects (`Motion`, `Timeline`, `Stage`, `Actor`, `Script`)
- Use any member function from your classes in a script (`Scriptable`)
- Add attributes to your classes for scripting, saving, and loading (`Attributes`, `ElementID`)

### Internationalization
 - Support multiple languages with `I18n`

### Color
- Color creation and manipulation (`mix()`, `change_hue()`, `change_lightness()`, etc.)
- Operators for ALLEGRO_COLORs (`+`, `-`, `*`, `==`)
- Many color definitions (`color::yellowgreen`, `color::blue`, `color::plum`, `color::floralwhite`, etc.)

### Encryption
- md5 and sha2 functions

### Other cool stuff (requires dependencies)
- Interprocess and Shared Memory (boost)
- Text-to-speech API (windows)
- Download a file in a thread (curl)
- Webcam access (OpenCV)
- MIDI control (windows)

### And More
- Bone trees, profiling timers, file path access, php-like functions, chainable media objects, etc.


