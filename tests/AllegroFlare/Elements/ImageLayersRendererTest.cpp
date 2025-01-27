
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/ImageLayersRenderer.hpp>


TEST(AllegroFlare_Elements_ImageLayersRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::ImageLayersRenderer image_layers_renderer;
}


/*
AllegroFlare::Elements::ImageLayer


  - name: tmj_id
    type: int
    init_with: 0
    constructor_arg: true
    exposed: true

  - name: name
    type: std::string
    init_with: '"[unset-name]"'
    constructor_arg: true
    exposed: true

  - name: image_filename
    type: std::string
    init_with: '"[unset-image_filename]"'
    constructor_arg: true
    exposed: true

  - name: bitmap
    type: ALLEGRO_BITMAP*
    init_with: nullptr
    constructor_arg: true
    exposed: true

  - name: bitmap_is_owned
    type: bool
    init_with: false
    constructor_arg: true
    exposed: true

  - name: pixel_scale
    type: int
    init_with: 1
    constructor_arg: true
    exposed: true

  - name: offset_x
    type: float
    init_with: 0.0f
    constructor_arg: true
    exposed: true

  - name: offset_y
    type: float
    init_with: 0.0f
    constructor_arg: true
    exposed: true

  - name: parallax_x
    type: float
    init_with: 0.0f
    constructor_arg: true
    exposed: true

  - name: parallax_y
    type: float
    init_with: 0.0f
    constructor_arg: true
    exposed: true

  - name: repeat_x
    type: bool
    init_with: false
    constructor_arg: true
    exposed: true

  - name: repeat_y
    type: bool
    init_with: false
    constructor_arg: true
    exposed: true

  - name: opacity
    type: float
    init_with: 0.0f
    constructor_arg: true
    exposed: true

  - name: tint_color_is_set
    type: bool
    init_with: false
    constructor_arg: true
    exposed: true

  - name: tint_color
    type: ALLEGRO_COLOR
    init_with: DEFAULT_TINT_COLOR
    constructor_arg: true
    exposed: true

  - name: destroyed
    type: bool
    init_with: false
    constructor_arg: true
    exposed: true

  - name: DEFAULT_TINT_COLOR
    type: ALLEGRO_COLOR
    init_with: 'ALLEGRO_COLOR{1, 1, 1, 1}'
    static: true
    constexpr: true


*/


