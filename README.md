![](http://zeoxdesign.com/images/allegro_flare_logo-04.png) AllegroFlare
=============

Current version - v0.8.8wip


AllegroFlare is a C++ application toolkit that extends the functionality of the Allegro 5 game programming library.  Every part of the existing Allegro 5 library remains intact when using AllegroFlare.  AllegroFlare also includes an optional Framework class that makes for fast and fun development, or, you can cherry-pick any of the fantastic classes and functions provided by AllegroFlare without using the framework at all.



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
Success!  The only thing left to do is `#include <allegro_flare/allegro_flare.h>` in your program and link with the AllegroFlare lib and the Allegro libs when compiling.  Optionally, you can build the example programs with `make examples`.



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
- Use virtual member functions to grab events (`primary_timer_func()`, `mouse_axes_func()`, `joy_button_down_func()`, `key_char_func()`, etc)
- Get any asset by filename (`Framework::bitmap("mypic.jpg")`, `Framework::font("Times.ttf 16")`, etc)

### Resource Management
- Bins for media files (`FontBin`, `SampleBin`, `BitmapBin`)
- Use any image, sample, or font by filename

### Graphics
- 2D path shapes (`path2d`)
- 2D and 3D positioning tools (`vec2d`, `vec3d`, `placement2d`, `placement3d`)
- cameras (`Camera2D`, `Camera3D`)
- 3D model loading (`Model3D`)
- Basic image manipulation (`gaussian_blur()`, `color_overlay()`, `trim()`, `color_curve()`, `invert()`, etc)
- Image generation (`draw_wav_sample()`, `draw_histogram()`, `create_gradient_bitmap()`, etc)
- Create music notation (`MusicNotation`)
- Offscreen bitmaps / Cache expensive renders (`RenderCache`)

### GUI
- Interface with the GUI through the parent class `UIScreen`
- Use from a list of usefull widgets `UIButton`, `UICheckbox`, `UIDial`, `UIFramedWindow`, `UIImage`, `UIIntSpinner`, `UILabeledCheckbox`, `UIListSpinner`, `UIMusicNotation`, `UIPickingBuffer`, `UIProgressBar`, `UIScaledText`, `UIScreen`, `UIScrollArea`, `UIScrollBar`, `UISpinner`, `UIVerticalSlider`, `UIText`, `UITextArea`, `UITextBox`, `UITextInput`, `UITextList`, `UIToggleButton`, `UIXYController`, `UIWidget`, `UIWindow`
- Easily create your own widget by inheriting from `UIWidget`

### Motion
- timing and movement control (`Motion`)
- easing functions (`interpolator::fastIn`, `interpolator::trippleSlowInOut`, `interpolator::bounceIn`, etc)

### Scripting and Animation
- Use useful clases to automate playback of your objects (`Motion`, `Timeline`, `Stage`, `Actor`, `Script`)
- Use any member function from your classes in a script (`Scriptable`)
- Add attributes to your classes for scripting, saving, and loading (`Attributes`, `ElementID`)

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


