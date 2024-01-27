# How to Create 2D Sprite Animations



## Using Aseprite to Design Your Animations

### Setup a New Sprite Sheet

* Create an image. The dimensions should be multiples of the sprite sizes (32x32
  sprites, 8 sprites in a column, then image width == 256). You could drop a few
  images in in the frames now if you like. You can also do this after the next
  step.

* `File` > `Import Sprite Sheet` - This will create a new image with the frames.

* Save the file as an ASE format. This is your new working file.

### Edit the Sprite Sheet

* Create a "loop seciton" - In the timeline, click-drag the numbers (or click, shift-click the next) 
  you want to be in the loop. Right click one of the numbers, then select "Set
  Loop Section (F2)".

* You can then edit the loop section

* Press ENTER to toggle playing the animation when one of the frames are selected in the timeline.

* You can change the duration of the frame by right clicking the frame number in
  the timeline > "Frame Properties" (also double-click the frame number). With
  multiple frames selected you can also change them by right-clicking the number
  and going to "Frame Properties".

* For AllegroFlare, append an `@` character to the name of the loop to indicate
  that it is a "play once" animation.
 
### Export the Sprite Sheet

* `File` > `Export Sprite Sheet`
  * In the `Layout` tab, choose "By Rows" and "Fixed # of Columns".  8 columns
    is a good number.
  * In the `Output` tab, to output the image file and the JSON data.
  * Note that if you make changes, you can `File` > `Repeat Last Export` (or Shift+Command+X) for convenience.

## Using the Animations in AllegroFlare

The components in the domain `AllegroFlare/FrameAnimation/*` are used to handle frame animations.

The easiest way to get started is to create an animation book (`AllegroFlare::FrameAnimation::Book`). This class contains the image and animation data, and allows you to reference the animations by name. To set it up, pass in the sprite sheet PNG and JSON filenames, and initialize the animation book like this:

```
   AllegroFlare::FrameAnimation::Book animation_book;
   animation_book.set_png_source_filename(get_fixtures_path() + "bitmaps/my_sprite_sheet.png");
   animation_book.set_json_source_filename(get_fixtures_path() + "bitmaps/my_sprite_sheet.json");
   animation_book.set_sprite_sheet_cell_width(32);
   animation_book.set_sprite_sheet_cell_height(32);
   animation_book.initialize();
```

Note that the `Platforming2D` prototype has a `AllegroFlare/Prototypes/Platforming2D/Entities/FrameAnimated2D` entity type, which contains convenience methods for animation.

```
AllegroFlare::Prototypes::Platforming2D::Entities::FrameAnimated2D frame_animated2d_entity(&animation_book);
// Some examples of controls with the Entities/FrameAnimated2D:
frame_animated2d_entity.set_animation("blob");
frame_animated2d_entity.set_animation_playback_rate(2.0); // Will playback at twice the speed
```

For some more complete examples, check out the tests for `AllegroFlare/Prototypes/Platforming2D/Screen`.
