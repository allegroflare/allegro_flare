
#include <gtest/gtest.h>

#include <AllegroFlare/Layouts/Layer.hpp>


TEST(AllegroFlare_Layouts_LayerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Layouts::Layer layer;
}

/*

  - name: offset_x
    type: float
    init_with: 0.0f
    exposed: true

  - name: offset_y
    type: float
    init_with: 0.0f
    exposed: true

  - name: num_rows
    type: int
    init_with: -1
    exposed: true

  - name: num_columns
    type: int
    init_with: -1
    exposed: true

  - name: tilelayers_tile_data
    type: std::map<std::string, std::vector<int>>
    init_with: '{}'
    exposed: true

  - name: objects
    type: std::vector<AllegroFlare::Tiled::TMJObject>
    init_with: '{}'
    exposed: true




  - name: text_slots
    type: std::map<std::string, AllegroFlare::Layouts::Elements::Text>
    init_with: '{}'
    constructor_arg: true
    setter: before_initialized

  - name: text_data
    type: std::map<std::string, std::string>
    init_with: '{}'
    getter: true
    setter: explicit
*/

